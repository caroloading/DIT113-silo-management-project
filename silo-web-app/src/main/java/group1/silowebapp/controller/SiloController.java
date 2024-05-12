package group1.silowebapp.controller;

import group1.silowebapp.repository.SiloRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;

import java.time.Year;

@Controller
public class SiloController {
    @Autowired
    private SiloRepository siloRepository;

    @GetMapping("/silos")
    public String getSilos(Model silos) {
        silos.addAttribute("silos", siloRepository.findAll());
        silos.addAttribute("thisYear", Year.now());
        return "silos";
    }

    @GetMapping("/silos/{id}")
    public String getSilo(@PathVariable("id") String siloId, Model silo) {
        silo.addAttribute("silo", siloRepository.findById(Long.parseLong(siloId)));
        silo.addAttribute("thisYear", Year.now());

        return "siloDetail";
    }
}
