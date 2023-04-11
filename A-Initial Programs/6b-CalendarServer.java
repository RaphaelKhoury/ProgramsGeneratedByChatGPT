import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

public class CalendarServer {
   private List<CalendarDate> calendarDates = new ArrayList<>();
   
   public void startServer() throws IOException, ClassNotFoundException {
      ServerSocket serverSocket = new ServerSocket(1234);
      
      while (true) {
         Socket clientSocket = serverSocket.accept();
         ObjectInputStream objectInputStream = new ObjectInputStream(clientSocket.getInputStream());
         CalendarDate calendarDate = (CalendarDate) objectInputStream.readObject();
         calendarDates.add(calendarDate);
         objectInputStream.close();
         clientSocket.close();
      }
   }
   
   public List<CalendarDate> getCalendarDates() {
      return calendarDates;
   }
   
   public static void main(String[] args) throws IOException, ClassNotFoundException {
      CalendarServer server = new CalendarServer();
      server.startServer();
   }
}
