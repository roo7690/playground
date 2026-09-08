package util;

import java.util.Scanner;

public final class ConsolePrompts {
    private ConsolePrompts() {
    }

    public static String askValidIp(Scanner scanner, String prompt) {
        while (true) {
            System.out.print(prompt);
            String ip = scanner.nextLine().trim();
            if (InputValidator.isValidIpAddress(ip)) {
                return ip;
            }
            System.out.println("Adresse IP invalide. Elle doit contenir quatre octets entre 0 et 255.");
        }
    }

    public static int askValidPort(Scanner scanner, String prompt) {
        while (true) {
            System.out.print(prompt);
            String port = scanner.nextLine().trim();
            if (InputValidator.isValidPort(port)) {
                return Integer.parseInt(port);
            }
            System.out.println("Port invalide. Le port doit etre entre 5000 et 5050.");
        }
    }

    public static String askNonBlank(Scanner scanner, String prompt) {
        while (true) {
            System.out.print(prompt);
            String value = scanner.nextLine().trim();
            if (!value.isBlank()) {
                return value;
            }
            System.out.println("La valeur ne peut pas etre vide.");
        }
    }
}
