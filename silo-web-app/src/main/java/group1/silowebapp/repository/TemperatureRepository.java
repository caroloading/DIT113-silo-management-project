package group1.silowebapp.repository;

import group1.silowebapp.model.Temperature;
import org.springframework.data.repository.CrudRepository;

import java.util.List;

public interface TemperatureRepository extends CrudRepository<Temperature, Long> {

    /* The CRUD-related methods in CrudRepository and the query methods declared
     * below will be AUTO IMPLEMENTED by Spring Boot.
     */
    List<Temperature> findAllByOrderByDateTimeDesc();

    Temperature findTopByOrderByDateTimeDesc();
}