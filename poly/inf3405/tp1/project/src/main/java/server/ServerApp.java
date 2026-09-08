package server;

import util.ConsolePrompts;
import util.Protocol;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.*;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.file.Path;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Locale;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public final class ServerApp {
    private static final DateTimeFormatter LOG_DATE_FORMAT = DateTimeFormatter.ofPattern("yyyy-MM-dd@HH:mm:ss");

    private final Scanner scanner;

    public ServerApp(Scanner scanner) {
        this.scanner = scanner;
    }

    public void start() throws IOException {
        String ip = ConsolePrompts.askValidIp(scanner, "Adresse IP du serveur: ");
        int port = ConsolePrompts.askValidPort(scanner, "Port d'ecoute (5000-5050): ");
        UserDatabase userDatabase = new UserDatabase(Path.of("users.db"));

        try (ServerSocket serverSocket = new ServerSocket()) {
            serverSocket.bind(new InetSocketAddress(ip, port));
            System.out.println("Serveur en ecoute sur " + ip + ":" + port);

            ExecutorService clientPool = Executors.newCachedThreadPool();
            while (true) {
                Socket clientSocket = serverSocket.accept();
                clientPool.submit(() -> handleClient(clientSocket, userDatabase));
            }
        }
    }

    private void handleClient(Socket socket, UserDatabase userDatabase) {
        try (socket;
             DataInputStream input = new DataInputStream(socket.getInputStream());
             DataOutputStream output = new DataOutputStream(socket.getOutputStream())) {

            String username = input.readUTF();
            String password = input.readUTF();

            if (!userDatabase.authenticateOrCreate(username, password)) {
                output.writeUTF(Protocol.AUTH_BAD_PASSWORD);
                output.flush();
                return;
            }

            output.writeUTF(Protocol.AUTH_OK);
            output.flush();

            String originalFileName = input.readUTF();
            String outputFileName = input.readUTF();
            int imageSize = input.readInt();
            if (imageSize <= 0) {
                throw new IOException("Taille d'image invalide.");
            }

            byte[] imageBytes = input.readNBytes(imageSize);
            if (imageBytes.length != imageSize) {
                throw new IOException("Image incomplete recue du client.");
            }

            logImageReceived(username, socket, originalFileName);
            byte[] processedImage = ImageProcessor.applySobel(imageBytes, outputFileName);

            output.writeUTF(outputFileName);
            output.writeInt(processedImage.length);
            output.write(processedImage);
            output.flush();
        } catch (IOException e) {
            System.err.println("Erreur pendant le traitement d'un client: " + e.getMessage());
        }
    }

    private static void logImageReceived(String username, Socket socket, String originalFileName) {
        String clientAddress = socket.getInetAddress().getHostAddress() + ":" + socket.getPort();
        String timestamp = LocalDateTime.now().format(LOG_DATE_FORMAT);
        System.out.printf("[%s - %s - %s] : Image %s recue pour traitement.%n",
                username, clientAddress, timestamp, originalFileName);
    }

    public static final class ImageProcessor {
        private ImageProcessor() {
        }

        public static byte[] applySobel(byte[] inputBytes, String outputFileName) throws IOException {
            BufferedImage input = ImageIO.read(new ByteArrayInputStream(inputBytes));
            if (input == null) {
                throw new IOException("Format d'image non supporte ou fichier invalide.");
            }

            BufferedImage output = Sobel.process(input);
            String format = imageFormat(outputFileName);

            try (ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream()) {
                if (!ImageIO.write(output, format, byteArrayOutputStream)) {
                    throw new IOException("Impossible d'ecrire l'image au format " + format + ".");
                }
                return byteArrayOutputStream.toByteArray();
            }
        }

        private static String imageFormat(String fileName) {
            int dot = fileName.lastIndexOf('.');
            if (dot < 0 || dot == fileName.length() - 1) {
                return "png";
            }

            String extension = fileName.substring(dot + 1).toLowerCase(Locale.ROOT);
            if (extension.equals("jpg") || extension.equals("jpeg")) {
                return "jpg";
            }
            if (extension.equals("bmp") || extension.equals("gif")) {
                return extension;
            }
            return "png";
        }
    }
}
