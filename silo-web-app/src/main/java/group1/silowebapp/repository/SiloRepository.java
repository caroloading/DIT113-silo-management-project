package group1.silowebapp.repository;

import org.springframework.data.repository.CrudRepository;
import group1.silowebapp.model.Silo;

public interface SiloRepository extends CrudRepository<Silo, Long> {

  /* The CRUD-related methods in CrudRepository and the query methods declared 
   * below will be AUTO IMPLEMENTED by Spring Boot.
   */
  Silo findById(long id);
}