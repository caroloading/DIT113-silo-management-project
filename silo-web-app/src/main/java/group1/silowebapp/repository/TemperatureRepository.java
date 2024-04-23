package group1.silowebapp.repository;

import group1.silowebapp.model.Temperature;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;

import java.util.List;

public interface TemperatureRepository extends CrudRepository<Temperature, Long> {

    /* The CRUD-related methods in CrudRepository and the query methods declared
     * below will be AUTO IMPLEMENTED by Spring Boot.
     */
    Temperature findById(long id);

    Temperature findTopByOrderByDateTimeDesc();

    /* By default, @Query accepts JPQL queries (used below).
     * It also allows for running native queries by setting the nativeQuery flag
     * to true (however, database platform independence is then lost)
     */
    @Query("SELECT t FROM Temperature t WHERE t.dateTime LIKE ?1%")
    List<Temperature> findByDate(String dateTime);
}