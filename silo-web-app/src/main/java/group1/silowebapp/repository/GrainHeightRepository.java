package group1.silowebapp.repository;

import group1.silowebapp.model.GrainHeight;
import org.springframework.data.repository.CrudRepository;

import java.util.List;

public interface GrainHeightRepository extends CrudRepository<GrainHeight, Long> {

    /* The CRUD-related methods in CrudRepository and the query methods declared
     * below will be AUTO IMPLEMENTED by Spring Boot.
     */
<<<<<<< HEAD

=======
>>>>>>> main
    List<GrainHeight> findAllByOrderByDateTimeDesc();

    GrainHeight findTopByOrderByDateTimeDesc();
}