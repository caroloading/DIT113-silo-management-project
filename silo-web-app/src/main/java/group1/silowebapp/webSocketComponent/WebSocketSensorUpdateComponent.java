package group1.silowebapp.webSocketComponent;

import group1.silowebapp.model.GrainHeight;
import group1.silowebapp.model.Humidity;
import group1.silowebapp.model.Temperature;

import java.util.Locale;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.stereotype.Component;



@Component
public class WebSocketSensorUpdateComponent {
    @Autowired
    private SimpMessagingTemplate messagingTemplate;

    private final Notification tempNotification;
    private final Notification humNotification;
    private final Notification distanceNotification;

    public WebSocketSensorUpdateComponent(){
        tempNotification = new Notification("temperature", false);
        humNotification = new Notification("humidity", false);
        distanceNotification = new Notification("distance", false);
    }

    public void updateTemperature(Temperature temperature) {  
        messagingTemplate.convertAndSend("/topic/temperatures/update", temperature);

        if (temperature.getOutOfBounds() && !tempNotification.getWarningOn()){
            tempNotification.setWarningOn(true);
            sendNotification(tempNotification);
        } else if (!temperature.getOutOfBounds() && tempNotification.getWarningOn()){
            tempNotification.setWarningOn(false);
            sendNotification(tempNotification);
        }
    }

    public void updateHumidity(Humidity humidity) {
        messagingTemplate.convertAndSend("/topic/humidity/update", humidity);

        if (humidity.getOutOfBounds() && !humNotification.getWarningOn()){
            humNotification.setWarningOn(true);
            sendNotification(humNotification);
        } else if (!humidity.getOutOfBounds() && humNotification.getWarningOn()){
            humNotification.setWarningOn(false);
            sendNotification(humNotification);
        }
    }

    public void updateDistance(GrainHeight grainHeight) {
        
        Double percentage = grainHeight.getPercentage();
        String percentageString = String.format(Locale.ENGLISH, "%.2f", percentage);
        percentage = Double.parseDouble(percentageString);

        //creating object not linked to database, with percentage distance
        GrainPercentage grainPercentage = 
            new GrainPercentage(grainHeight.getId(), percentage, grainHeight.getDateTime());
        messagingTemplate.convertAndSend("/topic/distances/update", grainPercentage);

        if (grainHeight.getOutOfBounds() && !distanceNotification.getWarningOn()){
            distanceNotification.setWarningOn(true);
            sendNotification(distanceNotification);
        } else if (!grainHeight.getOutOfBounds() && distanceNotification.getWarningOn()){
            distanceNotification.setWarningOn(false);
            sendNotification(distanceNotification);
        }
    }

    private void sendNotification(Notification notification){
        System.out.println("notif sent" + notification.getWarningType() + notification.getWarningOn());
        messagingTemplate.convertAndSend("/topic/notification", notification);
    }

    public void setUpWarningStatus(boolean temp, boolean hum, boolean distance){
        tempNotification.setWarningOn(temp);
        humNotification.setWarningOn(hum);
        distanceNotification.setWarningOn(distance);
        sendNotification(tempNotification);
        sendNotification(humNotification);
        sendNotification(distanceNotification);
    }

}
