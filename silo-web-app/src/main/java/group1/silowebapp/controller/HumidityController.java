package group1.silowebapp.controller;

import group1.silowebapp.repository.HumidityRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

/*
 * The @Autowired annotations allows Spring to inject beans into the controller.
 * In this case, the autowired reference allows us to query the Humidity
 * model (entity).
 *
 * The controller adds objects to the Model map. This map object is made available
 * to the view component.
 *
 */

@Controller
public class HumidityController {
    @Autowired
    private HumidityRepository humidityRepository;

    @GetMapping("/humidities")
    public String getAllHumidities(Model humidities) {
        humidities.addAttribute("humidities", humidityRepository.findAllByOrderByDateTimeDesc());

        return "humidities";
    }
}
