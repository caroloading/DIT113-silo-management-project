package group1.silowebapp.controller;

import group1.silowebapp.repository.TemperatureRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

import java.time.Year;

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
