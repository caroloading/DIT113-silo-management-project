package group1.silowebapp.controller;

import java.time.Year;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

import group1.silowebapp.model.GrainHeight;
import group1.silowebapp.model.Humidity;
import group1.silowebapp.model.Temperature;
import group1.silowebapp.repository.GrainHeightRepository;
import group1.silowebapp.repository.HumidityRepository;
import group1.silowebapp.repository.SiloRepository;
import group1.silowebapp.repository.TemperatureRepository;

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
		Temperature topTemp = temperatureRepository.findTopByOrderByDateTimeDesc() == null? 
			new Temperature(0.0, "", siloRepository.findById(1L)) : temperatureRepository.findTopByOrderByDateTimeDesc();

		Humidity topHumidity = humidityRepository.findTopByOrderByDateTimeDesc() == null? 
			new Humidity(0.0, "", siloRepository.findById(1L)) : humidityRepository.findTopByOrderByDateTimeDesc();
		
		GrainHeight topGrainHeight = grainHeightRepository.findTopByOrderByDateTimeDesc() == null? 
			new GrainHeight(0.0, "", siloRepository.findById(1L)) : grainHeightRepository.findTopByOrderByDateTimeDesc();
		
		model.addAttribute("temperature", topTemp);
		model.addAttribute("humidity", topHumidity);
		model.addAttribute("grainHeight", topGrainHeight);
		model.addAttribute("thisYear", Year.now());

		return "index";
	}

}
