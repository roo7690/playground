package util;

public final class InputValidator {
    private static final int MIN_PORT = 5000;
    private static final int MAX_PORT = 5050;

    private InputValidator() {
    }

    public static boolean isValidIpAddress(String value) {
        if (value == null || value.isBlank()) {
            return false;
        }

        String[] octets = value.trim().split("\\.", -1);
        if (octets.length != 4) {
            return false;
        }

        for (String octet : octets) {
            if (octet.isEmpty() || octet.length() > 3) {
                return false;
            }
            for (int i = 0; i < octet.length(); i++) {
                if (!Character.isDigit(octet.charAt(i))) {
                    return false;
                }
            }
            int numericValue = Integer.parseInt(octet);
            if (numericValue < 0 || numericValue > 255) {
                return false;
            }
        }
        return true;
    }

    public static boolean isValidPort(String value) {
        try {
            int port = Integer.parseInt(value.trim());
            return isValidPort(port);
        } catch (NumberFormatException e) {
            return false;
        }
    }

    public static boolean isValidPort(int port) {
        return port >= MIN_PORT && port <= MAX_PORT;
    }
}
