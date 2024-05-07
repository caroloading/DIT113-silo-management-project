package group1.silowebapp.webSocketComponent;

public class GrainPercentage {
    private Long id;
    private String percentage;
    private String dateTime;

    public GrainPercentage(Long id, String percentage, String dateTime){
        this.id = id;
        this.percentage = percentage;
        this.dateTime = dateTime;
    }

    public Long getId(){
        return id;
    }

    public String getPercentage(){
        return percentage;
    }

    public String getDateTime(){
        return dateTime;
    }

}
