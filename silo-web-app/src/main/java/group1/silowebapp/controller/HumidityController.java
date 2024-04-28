package group1.silowebapp.controller;

import group1.silowebapp.repository.HumidityRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

import java.time.Year;

@Controller
public class HumidityController {
    @Autowired
    private HumidityRepository humidityRepository;

    @GetMapping("/humidities")
    public String getAllHumidities(Model humidities) {
        humidities.addAttribute("humidities", humidityRepository.findAllByOrderByDateTimeDesc());
        humidities.addAttribute("thisYear", Year.now());

        return "humidities";
    }
}
