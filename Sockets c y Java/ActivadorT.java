import java.net.*;
import java.io.*;
import java.util.Scanner;

public class ActivadorT {
    public static void main(String[] args) throws Exception {
        Scanner scanner = new Scanner(System.in);

        System.out.print("introduce el puerto para el activador de temperatura: ");
        int puerto = scanner.nextInt();

        ServerSocket server = new ServerSocket(puerto);
        System.out.println("actuador de temperatura listo en puerto " + server.getLocalPort());

        while (true) {
            try (Socket socket = server.accept();
                 BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()))) {
                String mensaje = in.readLine();
                System.out.println("recibio: " + mensaje + "°C -> activando climatizador");
            }
        }
    }
}



