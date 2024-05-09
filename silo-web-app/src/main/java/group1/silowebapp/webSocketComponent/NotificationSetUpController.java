package group1.silowebapp.webSocketComponent;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.stereotype.Controller;

import group1.silowebapp.repository.GrainHeightRepository;
import group1.silowebapp.repository.HumidityRepository;
import group1.silowebapp.repository.TemperatureRepository;

@Controller
public class NotificationSetUpController {

    @Autowired
    private WebSocketSensorUpdateComponent webSocketSensorUpdateComponent;
    @Autowired
    private GrainHeightRepository grainHeightRepository;
    @Autowired
    private HumidityRepository humidityRepository;
    @Autowired 
    private TemperatureRepository temperatureRepository;

    //receiving message on page load,
    //getting the last sensors data
    //and calling the SetUpWarningStatus method 
    //to inform webpage of warning statuses.
    @MessageMapping("/send/warningSetUp")
    public void triggerNotifications(){
        boolean lastTempOutOfBounds = temperatureRepository.findTopByOrderByDateTimeDesc().isOutOfBounds();
        boolean lastHumOutOfBounds = humidityRepository.findTopByOrderByDateTimeDesc().isOutOfBounds();
        boolean lastDistanceOutOfBounds = grainHeightRepository.findTopByOrderByDateTimeDesc().isOutOfBounds();
        
        webSocketSensorUpdateComponent.setUpWarningStatus(lastTempOutOfBounds, lastHumOutOfBounds, lastDistanceOutOfBounds);
    }
}
