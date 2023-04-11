import java.util.Date;

public class CalendarDate {
   private Date date;
   private String description;
   
   public CalendarDate(Date date, String description) {
      this.date = date;
      this.description = description;
   }
   
   public Date getDate() {
      return date;
   }
   
   public String getDescription() {
      return description;
   }
   
   public void setDescription(String description) {
      this.description = description;
   }
}
