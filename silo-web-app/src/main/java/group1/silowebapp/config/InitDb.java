package group1.silowebapp.config;


import group1.silowebapp.model.GrainHeight;
import group1.silowebapp.model.Humidity;
import group1.silowebapp.model.Silo;
import group1.silowebapp.model.Temperature;
import group1.silowebapp.repository.GrainHeightRepository;
import group1.silowebapp.repository.HumidityRepository;
import group1.silowebapp.repository.SiloRepository;
import group1.silowebapp.repository.TemperatureRepository;

import java.time.LocalTime;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.CommandLineRunner;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

/*
 * This class initializes the database with mockup data for testing purpose.
 * It will be removed in production mode.
 */
@Configuration
public class InitDb {

    private static final Logger log = LoggerFactory.getLogger(InitDb.class);


    @Bean("initializeDb")
    public CommandLineRunner initDbWithData(
            SiloRepository siloRepository, GrainHeightRepository grainHeightRepository,
            HumidityRepository humidityRepository, TemperatureRepository temperatureRepository) {
        return (args) -> {

            // SILO
            // save a few Silos
            siloRepository.save(new Silo(8.0, 4.0, "Wio terminal 01", "Seed Studio", "SAMD51"));
            siloRepository.save(new Silo(7.0, 3.0, "Wio terminal 02", "Seed Studio", "SAMD51"));

            final Silo firstSilo = siloRepository.findById(1L);

            // GrainHeight
            // save a few Grain heights
            grainHeightRepository.save(new GrainHeight(30.19, LocalTime.now().toString(), firstSilo));
            grainHeightRepository.save(new GrainHeight(33.20, LocalTime.now().toString(), firstSilo));

            // Humidity
            // save a few Humidities
            humidityRepository.save(new Humidity(33.32, LocalTime.now().toString(), firstSilo));
            humidityRepository.save(new Humidity(43.20, LocalTime.now().toString(), firstSilo));

            // Temperature
            // save a few Temperatures
            temperatureRepository.save(new Temperature(36.02, LocalTime.now().toString(), firstSilo));
            temperatureRepository.save(new Temperature(45.25, LocalTime.now().toString(), firstSilo));
        };
    }
}
 
