package group1.silowebapp.controller;

import group1.silowebapp.repository.GrainHeightRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

/*
 * The @Autowired annotations allows Spring to inject beans into the controller.
 * In this case, the autowired reference allows us to query the GrainHeight
 * model (entity).
 *
 * The controller adds objects to the Model map. This map object is made available
 * to the view component.
 *
 */

@Controller
public class GrainHeightController {
    @Autowired
    private GrainHeightRepository grainHeightRepository;

    @GetMapping("/grainheights")
    public String getAllGrainHeights(Model grainHeight) {
        grainHeight.addAttribute("grainHeights", grainHeightRepository.findAllByOrderByDateTimeDesc());

        return "grainheights";
    }
}
