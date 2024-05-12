package group1.silowebapp.controller;

import group1.silowebapp.model.EntityFactory;
import group1.silowebapp.model.GrainHeight;
import group1.silowebapp.model.Humidity;
import group1.silowebapp.model.Temperature;
import group1.silowebapp.repository.GrainHeightRepository;
import group1.silowebapp.repository.HumidityRepository;
import group1.silowebapp.repository.SiloRepository;
import group1.silowebapp.repository.TemperatureRepository;
import group1.silowebapp.schemas.SensorReading;
import group1.silowebapp.webSocketComponent.WebSocketSensorUpdateComponent;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;

import java.time.LocalTime;


/*
 * Controller class for page used for testing purposes
 * Will be removed before deployment.
 */
@Controller
public class WsHomeController {

    @Autowired
    private SiloRepository siloRepository;

    @Autowired
    private HumidityRepository humiRepo;
    @Autowired
    private TemperatureRepository tempRepo;
    @Autowired
    private GrainHeightRepository distanceRepo;

    @Autowired
    private WebSocketSensorUpdateComponent webSocketSensorUpdateComponent;

    @GetMapping("/ws/sensors")
    public String getSensorsHome(Model model) {
        model.addAttribute("reading", new SensorReading());

        return "wsSensors";
    }

    @PostMapping("/ws/sensors")
    public String callSensorsWebSocket(@ModelAttribute SensorReading reading, Model model) {
        String now = LocalTime.now().toString();

        Temperature temp = tempRepo.save(
                EntityFactory.createTemperature(
                        reading.getTemperature(),
                        now,
                        siloRepository.findById(1L)
                )
        );
        Humidity humidity = humiRepo.save(
                EntityFactory.createHumidity(
                        reading.getHumidity(),
                        now,
                        siloRepository.findById(1L)
                )
        );
        GrainHeight distance = distanceRepo.save(
                EntityFactory.createGrainHeight(
                        reading.getDistance(),
                        now,
                        siloRepository.findById(1L)
                )
        );

        webSocketSensorUpdateComponent.updateTemperature(temp);
        webSocketSensorUpdateComponent.updateHumidity(humidity);
        webSocketSensorUpdateComponent.updateDistance(distance);

        model.addAttribute("reading", new SensorReading());

        return "wsSensors";
    }
}
