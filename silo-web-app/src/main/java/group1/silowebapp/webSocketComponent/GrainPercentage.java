package group1.silowebapp.webSocketComponent;

//Class not linked to database
//for sending grain quantity data
//with percentages
public class GrainPercentage {
    private Long id;
    private Double percentage;
    private String dateTime;

    public GrainPercentage(Long id, Double percentage, String dateTime) {
        this.id = id;
        this.percentage = percentage;
        this.dateTime = dateTime;
    }

    public Long getId() {
        return id;
    }

    public Double getPercentage() {
        return percentage;
    }

    public String getDateTime() {
        return dateTime;
    }

}
