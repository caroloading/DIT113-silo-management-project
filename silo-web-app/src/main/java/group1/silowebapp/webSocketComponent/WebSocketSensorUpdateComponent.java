package group1.silowebapp.webSocketComponent;

import group1.silowebapp.model.GrainHeight;
import group1.silowebapp.model.Humidity;
import group1.silowebapp.model.Temperature;

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
        System.out.println("sending message");  
        messagingTemplate.convertAndSend("/topic/temperatures/update", temperature);

        tempNotification.setWarningOn(temperature.getOutOfBounds());
        sendNotification(tempNotification);
    }

    public void updateHumidity(Humidity humidity) {
        messagingTemplate.convertAndSend("/topic/humidity/update", humidity);

        humNotification.setWarningOn(humidity.getOutOfBounds());
        sendNotification(humNotification);
    }

    public void updateDistance(GrainHeight grainHeight) {

        Double percentage = grainHeight.getPercentage();
        String percentageString = String.format("%.2f", percentage);
        percentage = Double.parseDouble(percentageString);

        //creating object not linked to database, with percentage distance
        GrainPercentage grainPercentage = 
            new GrainPercentage(grainHeight.getId(), percentage, grainHeight.getDateTime());
        messagingTemplate.convertAndSend("/topic/distances/update", grainPercentage);

        distanceNotification.setWarningOn(grainHeight.getOutOfBounds());
        sendNotification(distanceNotification);
    }

    private void sendNotification(Notification notification){
        System.out.println("sent notification");
        messagingTemplate.convertAndSend("/topic/notification", notification);
    }
}
