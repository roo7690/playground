package client;

import java.io.IOException;
import java.util.Locale;
import java.util.Scanner;

public final class Main {
    private Main() {
    }

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            new ClientApp(scanner).start();
        } catch (IOException e) {
            System.err.println("Erreur reseau ou fichier: " + e.getMessage());
        }
    }
}
