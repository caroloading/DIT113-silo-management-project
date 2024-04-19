package group1.silowebapp.controller;

import java.time.Year;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

import group1.silowebapp.repository.TemperatureRepository;

@Controller
public class TemperatureController {
    @Autowired
	private TemperatureRepository temperatureRepository;

    @GetMapping("/temperatures")
	public String getAllTemperatures(Model temperatures) {
		temperatures.addAttribute("temperatures", temperatureRepository.findAll());
        temperatures.addAttribute("thisYear", Year.now());
		return "temperatures";
	}
}
