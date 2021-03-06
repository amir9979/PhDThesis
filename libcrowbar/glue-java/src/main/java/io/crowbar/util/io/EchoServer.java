package io.crowbar.util.io;

import java.io.InputStream;
import java.io.OutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public final class EchoServer extends ThreadedServer {
    public static final int MAX_SIZE = 100;

    private class EchoService implements Runnable {
        public EchoService (Socket s) {
            this.socket = s;
        }

        public void run () {
            try {
                while (socket.isConnected()) {
                    InputStream in = socket.getInputStream();

                    byte[] b = new byte[MAX_SIZE];
                    in.read(b);

                    OutputStream out = socket.getOutputStream();
                    out.write(b);
                    out.flush();
                }

                socket.close();
            }
            catch (IOException e) {
                e.printStackTrace();
            }
        }

        private Socket socket;
    }


    public EchoServer (ServerSocket serverSocket) {
        super(serverSocket);
    }

    @Override
    protected Runnable handle (Socket s) {
        return new EchoService(s);
    }
}