package client;

import util.ConsolePrompts;
import util.Protocol;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Scanner;

public final class ClientApp {
    private final Scanner scanner;

    public ClientApp(Scanner scanner) {
        this.scanner = scanner;
    }

    public void start() throws IOException {
        String serverIp = ConsolePrompts.askValidIp(scanner, "Adresse IP du serveur: ");
        int serverPort = ConsolePrompts.askValidPort(scanner, "Port du serveur (5000-5050): ");
        String username = ConsolePrompts.askNonBlank(scanner, "Nom d'utilisateur: ");
        String password = ConsolePrompts.askNonBlank(scanner, "Mot de passe: ");

        try (Socket socket = new Socket(serverIp, serverPort);
             DataInputStream input = new DataInputStream(socket.getInputStream());
             DataOutputStream output = new DataOutputStream(socket.getOutputStream())) {

            output.writeUTF(username);
            output.writeUTF(password);
            output.flush();

            String authResponse = input.readUTF();
            if (Protocol.AUTH_BAD_PASSWORD.equals(authResponse)) {
                System.out.println("Erreur dans la saisie du mot de passe");
                return;
            }
            if (!Protocol.AUTH_OK.equals(authResponse)) {
                System.out.println("Connexion refusee par le serveur.");
                return;
            }

            Path inputImage = askExistingImage();
            String outputImageName = ConsolePrompts.askNonBlank(scanner, "Nom de l'image traitee a sauvegarder: ");
            byte[] imageBytes = Files.readAllBytes(inputImage);

            output.writeUTF(inputImage.getFileName().toString());
            output.writeUTF(outputImageName);
            output.writeInt(imageBytes.length);
            output.write(imageBytes);
            output.flush();
            System.out.println("Image envoyee au serveur pour traitement.");

            String returnedFileName = input.readUTF();
            int processedImageSize = input.readInt();
            byte[] processedImage = input.readNBytes(processedImageSize);
            if (processedImage.length != processedImageSize) {
                throw new IOException("Image traitee incomplete recue du serveur.");
            }

            Path outputPath = Path.of(returnedFileName).toAbsolutePath().normalize();
            Files.write(outputPath, processedImage);
            System.out.println("Image traitee recue et sauvegardee ici: " + outputPath);
        }
    }

    private Path askExistingImage() {
        while (true) {
            String fileName = ConsolePrompts.askNonBlank(scanner, "Nom de l'image a envoyer: ");
            Path path = Path.of(fileName);
            if (Files.isRegularFile(path)) {
                return path;
            }
            System.out.println("Fichier introuvable dans le repertoire courant: " + Path.of("").toAbsolutePath());
        }
    }
}
