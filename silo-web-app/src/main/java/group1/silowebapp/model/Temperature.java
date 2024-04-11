package group1.silowebapp.model;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.ManyToOne;

@Entity 
public class Temperature {
    /* Define the ORM. JPA/Hibernate converts the definitions to the 
     * appropriate SQL DDL statements
     */
    @Id
    @GeneratedValue(strategy=GenerationType.AUTO)
    private Long id;

    @Column(nullable=false)
    private Double tValue;
    
    @Column(nullable=false)
    private String dateTime; 

    @ManyToOne
    @JoinColumn(name = "mcu_id")
    private Mcu mcu;

    protected Temperature() {}

    public Temperature(Double tValue, String dateTime, Mcu mcu) {
      this.tValue = tValue;
      this.dateTime = dateTime;
      this.mcu = mcu;
    }

    public Long getId() {
        return id;
    }
    
    public Double getTValue() {
        return tValue;
    }    

    public String getDateTime() {
        // Todo: format dateTime
        return dateTime;
    }

    public Mcu getMcu() {
        return mcu;
    }

    @Override
    public String toString() {
      return String.format("Temperature[id=%d, value='%.2f', dateTime='%s']", id, tValue, dateTime);
    }
}
