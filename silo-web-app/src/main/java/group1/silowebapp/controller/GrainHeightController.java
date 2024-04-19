package group1.silowebapp.controller;

import java.time.Year;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

import group1.silowebapp.repository.GrainHeightRepository;

@Controller
public class GrainHeightController {
	@Autowired
	private GrainHeightRepository grainHeightRepository;

    @GetMapping("/grainheights")
	public String getAllGrainHeights(Model grainHeight) {
		grainHeight.addAttribute("grainHeights", grainHeightRepository.findAll());
        grainHeight.addAttribute("thisYear", Year.now());

		return "grainheights";
	}  
}
