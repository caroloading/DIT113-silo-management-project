package group1.silowebapp.repository;

import group1.silowebapp.model.Silo;
import org.springframework.data.repository.CrudRepository;

public interface SiloRepository extends CrudRepository<Silo, Long> {

    /* The CRUD-related methods in CrudRepository and the query methods declared
     * below will be AUTO IMPLEMENTED by Spring Boot.
     */
    Silo findById(long id);

    //for testing purposes
    Silo findByHeight(double height);
}