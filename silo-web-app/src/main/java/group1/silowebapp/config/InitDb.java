package group1.silowebapp.config;

import group1.silowebapp.model.Silo;
import group1.silowebapp.repository.SiloRepository;

import java.util.List;

import org.springframework.boot.CommandLineRunner;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

/*
 * This class initializes the database with mockup data for testing purpose.
 * It will be removed in production mode.
 */
@Configuration
public class InitDb {

    @Bean("initializeDb")
    public CommandLineRunner initDbWithData(SiloRepository siloRepository) {
        return (args) -> {

            // NOTE: add silos only if there is no silo entries in the database
            List<Silo> silos = (List<Silo>) siloRepository.findAll();
            if (silos.isEmpty()) {
                siloRepository.save(new Silo("Sadgrak Bloodfoot", 8.0, 4.0, "Wio terminal 01", "Seed Studio", "SAMD51", 11.936941, 57.706584));
            }
        };
    }
}
