package group1.silowebapp.repository;

import java.util.List;
import org.springframework.data.repository.CrudRepository;
import group1.silowebapp.model.Mcu;

public interface McuRepository extends CrudRepository<Mcu, Long> {

  /* The CRUD-related methods in CrudRepository and the query methods declared 
   * below will be AUTO IMPLEMENTED by Spring Boot.
   */
  Mcu findById(long id);
  List<Mcu> findByVendor(String vendor);
  List<Mcu> findByProdModel(String prodModel);
  
}