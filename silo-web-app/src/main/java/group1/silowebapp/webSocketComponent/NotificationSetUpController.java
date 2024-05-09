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

    @MessageMapping("/send/warningSetUp")
    public void triggerNotifications(){
        boolean lastTempOutOfBounds = temperatureRepository.findTopByOrderByDateTimeDesc().getOutOfBounds();
        boolean lastHumOutOfBounds = humidityRepository.findTopByOrderByDateTimeDesc().getOutOfBounds();
        boolean lastDistanceOutOfBounds = grainHeightRepository.findTopByOrderByDateTimeDesc().getOutOfBounds();
        
        webSocketSensorUpdateComponent.setUpWarningStatus(lastTempOutOfBounds, lastHumOutOfBounds, lastDistanceOutOfBounds);
    }
}
