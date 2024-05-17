package group1.silowebapp.webSocketComponent;

import group1.silowebapp.model.GrainHeight;
import group1.silowebapp.model.Humidity;
import group1.silowebapp.model.Temperature;
import group1.silowebapp.schemas.GrainPercentage;
import group1.silowebapp.schemas.Notification;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.stereotype.Component;

import java.util.Locale;


@Component
public class WebSocketSensorUpdateComponent {
    @Autowired
    private SimpMessagingTemplate messagingTemplate;

    private final Notification tempNotification;
    private final Notification humNotification;
    private final Notification distanceNotification;

    public WebSocketSensorUpdateComponent() {
        tempNotification = new Notification("temperature", false);
        humNotification = new Notification("humidity", false);
        distanceNotification = new Notification("distance", false);
    }

    public void updateTemperature(Temperature temperature) {
        messagingTemplate.convertAndSend("/topic/temperatures/update", temperature);

        if (temperature.isOutOfBounds() && !tempNotification.isWarningOn()) {
            tempNotification.setWarningOn(true);
            sendNotification(tempNotification);
        } else if (!temperature.isOutOfBounds() && tempNotification.isWarningOn()) {
            tempNotification.setWarningOn(false);
            sendNotification(tempNotification);
        }
    }

    public void updateHumidity(Humidity humidity) {
        messagingTemplate.convertAndSend("/topic/humidity/update", humidity);

        if (humidity.isOutOfBounds() && !humNotification.isWarningOn()) {
            humNotification.setWarningOn(true);
            sendNotification(humNotification);
        } else if (!humidity.isOutOfBounds() && humNotification.isWarningOn()) {
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

        if (grainHeight.isOutOfBounds() && !distanceNotification.isWarningOn()) {
            distanceNotification.setWarningOn(true);
            sendNotification(distanceNotification);
        } else if (!grainHeight.isOutOfBounds() && distanceNotification.isWarningOn()) {
            distanceNotification.setWarningOn(false);
            sendNotification(distanceNotification);
        }
    }

    private void sendNotification(Notification notification) {
        messagingTemplate.convertAndSend("/topic/notification", notification);
    }

    //Setting up the starting warning boolean of all notifications
    //on page load, then sending the notifications.
    public void setUpWarningStatus(boolean temp, boolean hum, boolean distance) {
        tempNotification.setWarningOn(temp);
        humNotification.setWarningOn(hum);
        distanceNotification.setWarningOn(distance);
        sendNotification(tempNotification);
        sendNotification(humNotification);
        sendNotification(distanceNotification);
    }

}
