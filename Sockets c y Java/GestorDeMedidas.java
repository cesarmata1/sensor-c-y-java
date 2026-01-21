import java.io.*;
import java.net.*;
import java.util.Scanner;

public class GestorDeMedidas {
    public static void main(String[] args) throws Exception {
        Scanner scanner = new Scanner(System.in);

        String ipTemp, ipLuz;
        int puertoTemp, puertoLuz;


        ipTemp = leerIP(scanner, "introduce la IP para temperatura: ");
        puertoTemp = leerPuerto(scanner, "introduce el puerto  para temperatura: ");

        ipLuz = leerIP(scanner, "introduce la IP para luz: ");
        puertoLuz = leerPuerto(scanner, "introduce el puerto  para luz: ");

        int puertoUDP = leerPuerto(scanner, "introduce el puerto para escuchar: ");

        DatagramSocket udpSocket = new DatagramSocket(puertoUDP);
        byte[] buffer = new byte[1024];

        while (true) {
            buffer = new byte[1024]; 
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
            udpSocket.receive(packet);
            String mensaje = new String(packet.getData(), 0, packet.getLength());
            System.out.println("gestor recibio: "  + "" + mensaje);

            String[] partes = mensaje.split(":");
            String tipo = partes[0];
            int medida = Integer.parseInt(partes[1]);

            if (tipo.equals("temperatura") && (medida < 19 || medida > 24)) {
                enviarATCP(new InetSocketAddress(ipTemp, puertoTemp), String.valueOf(medida));
            } else if (tipo.equals("luz") && medida < 200) {
                enviarATCP(new InetSocketAddress(ipLuz, puertoLuz), String.valueOf(medida));
            }
        }
    }

    private static String leerIP(Scanner scanner, String mensaje) {
        String ip;
        while (true) {
            System.out.print(mensaje);
            ip = scanner.nextLine();
            try {
                InetAddress.getByName(ip);
                break;
            } catch (UnknownHostException e) {
                System.out.println("IP no valida. Intenta de nuevo.");
            }
        }
        return ip;
    }

    private static int leerPuerto(Scanner scanner, String mensaje) {
        int puerto;
        while (true) {
            System.out.print(mensaje);
            if (scanner.hasNextInt()) {
                puerto = scanner.nextInt();
                scanner.nextLine(); 
                if (puerto >= 1 && puerto <= 65535) {
                    break;
                }
            } else {
                scanner.nextLine(); 
            }
            System.out.println("puerto no valido. intenta de nuevo.");
        }
        return puerto;
    }

    private static void enviarATCP(InetSocketAddress address, String mensaje) throws IOException {
        try (Socket socket = new Socket(address.getAddress(), address.getPort());
             PrintWriter out = new PrintWriter(socket.getOutputStream(), true)) {
            out.println(mensaje);
            System.out.println("gestor envio " + mensaje);
        }
    }
}



