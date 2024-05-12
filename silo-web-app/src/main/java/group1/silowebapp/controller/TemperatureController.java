package group1.silowebapp.controller;

import group1.silowebapp.repository.TemperatureRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

import java.time.Year;

/*
 * The @Autowired annotations allows Spring to inject beans into the controller.
 * In this case, the autowired reference allows us to query the Temperature
 * model (entity).
 *
 * The controller adds objects to the Model map. This map object is made available
 * to the view component.
 *
 * thisYear attribute is used in the footer section of the HTML page
 */

@Controller
public class TemperatureController {
    @Autowired
    private TemperatureRepository temperatureRepository;

    @GetMapping("/temperatures")
    public String getAllTemperatures(Model temperatures) {
        temperatures.addAttribute("temperatures", temperatureRepository.findAllByOrderByDateTimeDesc());
        temperatures.addAttribute("thisYear", Year.now());
        return "temperatures";
    }
}
