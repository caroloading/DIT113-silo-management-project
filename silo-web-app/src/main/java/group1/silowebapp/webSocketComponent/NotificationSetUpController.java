package group1.silowebapp.webSocketComponent;

import group1.silowebapp.model.GrainHeight;
import group1.silowebapp.model.Humidity;
import group1.silowebapp.model.Temperature;
import group1.silowebapp.repository.GrainHeightRepository;
import group1.silowebapp.repository.HumidityRepository;
import group1.silowebapp.repository.TemperatureRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.stereotype.Controller;

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

    //Receiving message on page load,
    //getting the last sensors data
    //and calling the SetUpWarningStatus method 
    //to inform webpage of warning statuses.
    @MessageMapping("/send/warningSetUp")
    public void triggerNotifications() {
        Temperature lastTemp = temperatureRepository.findTopByOrderByDateTimeDesc();
        Humidity lastHumidity = humidityRepository.findTopByOrderByDateTimeDesc();
        GrainHeight lastDistance = grainHeightRepository.findTopByOrderByDateTimeDesc();

        webSocketSensorUpdateComponent.setUpWarningStatus(
                lastTemp.isOutOfBounds(), lastHumidity.isOutOfBounds(), lastDistance.isOutOfBounds());
    }
}
