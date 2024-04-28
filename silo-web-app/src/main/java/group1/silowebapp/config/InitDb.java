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

            // fetch all Silos
            log.info("Silos found with findAll():");
            log.info("-------------------------------");
            siloRepository.findAll().forEach(silo -> {
                log.info(silo.toString());
            });
            log.info("");

            // fetch an individual Silo by ID
            Silo silo = siloRepository.findById(1L);
            log.info("Silo found with findById(1L):");
            log.info("--------------------------------");
            log.info(silo.toString());
            log.info("");

            final Silo firstSilo = siloRepository.findById(1L);

            // GrainHeight
            // save a few Grain heights
            grainHeightRepository.save(new GrainHeight(30.19, LocalTime.now().toString(), firstSilo));
            grainHeightRepository.save(new GrainHeight(33.20, LocalTime.now().toString(), firstSilo));
//
            // fetch all heights
            log.info("GrainHeights found with findAll():");
            log.info("-------------------------------");
            grainHeightRepository.findAll().forEach(grainHeight -> {
            	log.info(grainHeight.toString());
            });
            log.info("");
//
            // fetch an individual GrainHeight by ID
            GrainHeight grainHeight  = grainHeightRepository.findById(1L);
            log.info("GrainHeight found with findById(1L):");
            log.info("--------------------------------");
            log.info(grainHeight.toString());
            log.info("");
//
            // fetch heights by a given date
            //log.info("GrainHeights found with findByDate('2024-04-10'):");
            //log.info("-------------------------------");
            //grainHeightRepository.findByDate("2024-04-10").forEach(height -> {
            //	log.info(height.toString());
            //});
            //log.info("");
//
            // Humidity
            // save a few Humidities
            humidityRepository.save(new Humidity(33.32, LocalTime.now().toString(), firstSilo));
            humidityRepository.save(new Humidity(43.20, LocalTime.now().toString(), firstSilo));
//
            // fetch all Humidities
            log.info("Humidities found with findAll():");
            log.info("-------------------------------");
            humidityRepository.findAll().forEach(humidity -> {
                log.info(humidity.toString());
            });
            log.info("");
//
            // fetch an individual Humidity by ID
            Humidity humidity  = humidityRepository.findById(1L);
            log.info("Humidity found with findById(1L):");
            log.info("--------------------------------");
            log.info(humidity.toString());
            log.info("");

            // fetch humidities by a given date
            log.info("Humidity found with findByDate('2024-04-11'):");
            log.info("-------------------------------");
            humidityRepository.findByDate("2024-04-11").forEach(humid -> {
                log.info(humid.toString());
            });
            log.info("");

            // Temperature
            // save a few Temperatures
            temperatureRepository.save(new Temperature(36.02, LocalTime.now().toString(), firstSilo));
            temperatureRepository.save(new Temperature(45.25, LocalTime.now().toString(), firstSilo));

            // fetch all Temperatures
            log.info("Temperatures found with findAll():");
            log.info("-------------------------------");
            temperatureRepository.findAll().forEach(temperature -> {
                log.info(temperature.toString());
            });
            log.info("");

            // fetch an individual Temperatures by ID
            Temperature temperature  = temperatureRepository.findById(1L);
            log.info("Temperatures found with findById(1L):");
            log.info("--------------------------------");
            log.info(temperature.toString());
            log.info("");

            // fetch Temperatures by a given date
            log.info("Temperatures found with findByDate('2024-04-10'):");
            log.info("-------------------------------");
            temperatureRepository.findByDate("2024-04-11").forEach(temp -> {
                log.info(temp.toString());
            });
            log.info("");
        };
    }
}
 
