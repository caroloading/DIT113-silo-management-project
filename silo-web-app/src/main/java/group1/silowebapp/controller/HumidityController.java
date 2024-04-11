package group1.silowebapp.controller;

import java.time.Year;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

import group1.silowebapp.repository.HumidityRepository;

@Controller
public class HumidityController {
	@Autowired
	private HumidityRepository humidityRepository;

    @GetMapping("/humidities")
	public String getAllHumidities(Model humidities) {
		humidities.addAttribute("humidities", humidityRepository.findAll());
        humidities.addAttribute("thisYear", Year.now());

		return "humidities";
	}  
}
