package group1.silowebapp.repository;

import java.util.List;
 
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import group1.silowebapp.model.Humidity;

public interface HumidityRepository extends CrudRepository<Humidity, Long> {

  /* The CRUD-related methods in CrudRepository and the query methods declared 
   * below will be AUTO IMPLEMENTED by Spring Boot.
   */
  Humidity findById(long id);
  Humidity findTopByOrderByDateTimeDesc();

  /* By default, @Query accepts JPQL queries (used below). 
   * It also allows for running native queries by setting the nativeQuery flag 
   * to true (however, database platform independence is then lost)
  */
  @Query("SELECT h FROM Humidity h WHERE h.dateTime LIKE ?1%")
  List<Humidity> findByDate(String dateTime);
 
}