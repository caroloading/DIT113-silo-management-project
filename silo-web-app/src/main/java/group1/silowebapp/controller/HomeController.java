package group1.silowebapp.controller;

import group1.silowebapp.model.GrainHeight;
import group1.silowebapp.model.Humidity;
import group1.silowebapp.model.Temperature;
import group1.silowebapp.repository.GrainHeightRepository;
import group1.silowebapp.repository.HumidityRepository;
import group1.silowebapp.repository.SiloRepository;
import group1.silowebapp.repository.TemperatureRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

import java.time.Year;

/*
 * The @Autowired annotations allows Spring to inject beans into the controller.
 * In this case, the autowired repository references allow us to query the 
 * corresponding models (entities)
 * 
 * The controller adds objects to the Model map. This map object is made available 
 * to the view component.
 * 
 * thisYear attribute is used in the footer section of the HTML page 
 */

@Controller
public class HomeController {
    @Autowired
    private TemperatureRepository temperatureRepository;
    @Autowired
    private HumidityRepository humidityRepository;
    @Autowired
    private GrainHeightRepository grainHeightRepository;
    @Autowired
    private SiloRepository siloRepository;

    @GetMapping({"/", "/index"})
    public String showIndex(Model model) {

        Temperature topTemp = temperatureRepository.findTopByOrderByDateTimeDesc();
        topTemp = topTemp == null ? new Temperature(0.0, "", siloRepository.findById(1L)) : topTemp;

        Humidity topHumidity = humidityRepository.findTopByOrderByDateTimeDesc();
        topHumidity = topHumidity == null ? new Humidity(0.0, "", siloRepository.findById(1L)) : topHumidity;

        GrainHeight topGrainHeight = grainHeightRepository.findTopByOrderByDateTimeDesc();
        topGrainHeight = topGrainHeight == null ? new GrainHeight(0.0, "", siloRepository.findById(1L)) : topGrainHeight;

        model.addAttribute("temperature", topTemp);
        model.addAttribute("humidity", topHumidity);
        model.addAttribute("grainHeight", topGrainHeight);
        model.addAttribute("thisYear", Year.now());

        return "index";
    }

}
