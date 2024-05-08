package group1.silowebapp.webSocketComponent;

import group1.silowebapp.model.GrainHeight;
import group1.silowebapp.model.Humidity;
import group1.silowebapp.model.Silo;
import group1.silowebapp.model.Temperature;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.stereotype.Component;


@Component
public class WebSocketSensorUpdateComponent {
    @Autowired
    private SimpMessagingTemplate messagingTemplate;

    public void updateTemperature(Temperature temperature) {
        messagingTemplate.convertAndSend("/topic/temperatures/update", temperature);
    }

    public void updateHumidity(Humidity humidity) {
        messagingTemplate.convertAndSend("/topic/humidity/update", humidity);
    }

    public void updateDistance(GrainHeight grainHeight) {

        Double percentage = grainHeight.getPercentage();
        String percentageString = String.format("%.2f", percentage);
        percentage = Double.parseDouble(percentageString);

        //creating object not linked to database, with percentage distance
        GrainPercentage grainPercentage = 
            new GrainPercentage(grainHeight.getId(), percentage, grainHeight.getDateTime());
        messagingTemplate.convertAndSend("/topic/distances/update", grainPercentage);

        if (percentage >= 95.0){
            fullNotification(true);
        } else {
            fullNotification(false);
        }
    }

    private void fullNotification(boolean full){
        messagingTemplate.convertAndSend("/topic/notification", full);
    }
}
