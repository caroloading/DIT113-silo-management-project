package group1.silowebapp.webSocketComponent;

public class Notification {
    private String warningType;
    private boolean warningOn;

    public Notification(String type, boolean outOfBounds){
        this.warningType = type;
        this.warningOn = outOfBounds;
    }

    public String getWarningType(){
        return warningType;
    }

    public void setWarningOn(boolean outOfBounds){
        this.warningOn = outOfBounds;
    }
    
    public boolean isWarningOn(){
        return warningOn;
    }
}
