package group1.silowebapp.model;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.ManyToOne;

@Entity 
public class Humidity {
    /* Define the ORM. JPA/Hibernate converts the definitions to the  
     * appropriate SQL DDL statements
     */
    @Id
    @GeneratedValue(strategy=GenerationType.AUTO)
    private Long id;

    @Column(nullable=false)
    private Double hValue;

    @Column(nullable=false)
    private String dateTime; 

    @ManyToOne
    @JoinColumn(name = "silo_id")
    private Silo silo;

    protected Humidity() {}

    public Humidity(Double hValue, String dateTime, Silo silo) {
      this.hValue = hValue;
      this.dateTime = dateTime;
      this.silo = silo;
    }

    public Long getId() {
        return id;
    }
    
    public Double getHValue() {
        return hValue;
    }    

    public String getDateTime() {
        //Todo: format 
        return dateTime;
    }

    public Silo getSilo() {
        return silo;
    }

    @Override
    public String toString() {
      return String.format("Humidity[id=%d, value='%.2f', dateTime='%s']", id, hValue, dateTime);
    }
}
