package group1.silowebapp.repository;

import group1.silowebapp.model.GrainHeight;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;

import java.util.List;

public interface GrainHeightRepository extends CrudRepository<GrainHeight, Long> {

    /* The CRUD-related methods in CrudRepository and the query methods declared
     * below will be AUTO IMPLEMENTED by Spring Boot.
     */
    GrainHeight findById(long id);

    GrainHeight findTopByOrderByDateTimeDesc();

    /* By default, @Query accepts JPQL queries (used below).
     * It also allows for running native queries by setting the nativeQuery flag
     * to true (however, database platform independence is then lost)
     */
    @Query("SELECT g FROM GrainHeight g WHERE g.dateTime LIKE ?1%")
    List<GrainHeight> findByDate(String dateTime);
}