package server;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Base64;
import java.util.LinkedHashMap;
import java.util.Map;

public final class UserDatabase {
    private final Path databaseFile;
    private final Map<String, String> users = new LinkedHashMap<>();

    public UserDatabase(Path databaseFile) throws IOException {
        this.databaseFile = databaseFile;
        load();
    }

    public synchronized boolean authenticateOrCreate(String username, String password) throws IOException {
        String encodedPassword = encode(password);
        String storedPassword = users.get(username);
        if (storedPassword == null) {
            users.put(username, encodedPassword);
            save();
            return true;
        }
        return storedPassword.equals(encodedPassword);
    }

    private void load() throws IOException {
        if (!Files.exists(databaseFile)) {
            return;
        }

        try (BufferedReader reader = Files.newBufferedReader(databaseFile, StandardCharsets.UTF_8)) {
            String line;
            while ((line = reader.readLine()) != null) {
                int separator = line.indexOf('=');
                if (separator <= 0) {
                    continue;
                }
                users.put(line.substring(0, separator), line.substring(separator + 1));
            }
        }
    }

    private void save() throws IOException {
        try (BufferedWriter writer = Files.newBufferedWriter(databaseFile, StandardCharsets.UTF_8)) {
            for (Map.Entry<String, String> entry : users.entrySet()) {
                writer.write(entry.getKey());
                writer.write('=');
                writer.write(entry.getValue());
                writer.newLine();
            }
        }
    }

    private static String encode(String value) {
        return Base64.getEncoder().encodeToString(value.getBytes(StandardCharsets.UTF_8));
    }
}
