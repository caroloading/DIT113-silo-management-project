package group1.silowebapp.controller;

import java.time.Year;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

import group1.silowebapp.repository.GrainHeightRepository;
import group1.silowebapp.repository.HumidityRepository;
import group1.silowebapp.repository.TemperatureRepository;

@Controller
public class HomeController {
	@Autowired
	private TemperatureRepository temperatureRepository;
	@Autowired
	private HumidityRepository humidityRepository;
	@Autowired
	private GrainHeightRepository grainHeightRepository;

	private Year thisYear = Year.now();

	@GetMapping({"/", "/index"})
	public String showIndex(Model model) {
		model.addAttribute("temperature", temperatureRepository.findTopByOrderByDateTimeDesc());
		model.addAttribute("humidity", humidityRepository.findTopByOrderByDateTimeDesc());
		model.addAttribute("grainHeight", grainHeightRepository.findTopByOrderByDateTimeDesc());
		model.addAttribute("thisYear", thisYear);

		return "index";
	}

}
