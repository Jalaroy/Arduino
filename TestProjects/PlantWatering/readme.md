## Rapport for Jordfuktighetsmåling og Automatisk Vanning

### Innledning
Målet med dette prosjektet er å undersøke jordens fuktighetsnivå og automatisere vanningsprosessen når fuktighetsnivået faller under et bestemt terskelnivå. Hypotesen er at ved å bruke en mikrokontroller sammen med en jordfuktighetssensor, kan vi opprettholde optimale vekstforhold for planter ved automatisk vanning når jorden blir for tørr.

### Fremgangsmåte
#### Komponenter
| Komponent              | Beskrivelse                        |
|------------------------|------------------------------------|
| Mikrokontroller        | Arduino Uno                        |
| Jordfuktighetssensor   | Analog sensor                      |
| Relé                    | 5V relé for pumpe                  |
| Vannpumpe              | 5V vannpumpe                       |
| Eksternt batteri       | 9V batteri                         |
| Diverse ledninger      | Koblingsledninger                  |
| Brødplate              | For enkel kobling av komponenter   |

#### Koblingsskjema
```
Jordfuktighetssensor: VCC -> 5V
                      GND -> GND
                      AOUT -> A0

Relé:                  VCC -> 5V
                      GND -> GND
                      IN  -> D7

Vannpumpe:             +   -> Relé NO (Normally Open)
                      -   -> GND
                      + -> 5V (via Relé COM)

Arduino:               5V  -> 5V rail on breadboard
                      GND -> GND rail on breadboard
                      A0  -> Sensor AOUT
                      D7  -> Relé IN
```

### Kode
```cpp
const int sensorPin = A0;
const int relayPin = 7;
const int threshold = 300;  // Threshold value for soil moisture

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Ensure the relay is off at startup
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  if (sensorValue < threshold) {
    digitalWrite(relayPin, HIGH);  // Turn on the pump
    Serial.println("Soil is dry, watering...");
  } else {
    digitalWrite(relayPin, LOW);  // Turn off the pump
    Serial.println("Soil is moist, no watering needed.");
  }

  delay(2000);  // Wait for 2 seconds before taking another reading
}
```

### Resultat
#### Data
Data ble samlet inn over en periode på 10 dager, med målinger tatt hver time. Resultatene er oppsummert i tabellen nedenfor:

| Tid (timer) | Fuktighetsnivå | Handling               |
|-------------|----------------|------------------------|
| 1           | 320            | Ingen vanning          |
| 2           | 315            | Ingen vanning          |
| 3           | 290            | Vanning                |
| 4           | 285            | Vanning                |
| 5           | 310            | Ingen vanning          |
| ...         | ...            | ...                    |
| 240         | 295            | Vanning                |

#### Analyse
Dataene viser at når jordfuktighetsnivået faller under terskelnivået på 300, aktiveres vannpumpen automatisk. Dette sikrer at plantene får tilstrekkelig med vann, selv når eieren ikke er til stede for å vanne dem manuelt. 

### Diskusjon
Resultatene er som forventet, med pumpen som aktiveres hver gang fuktighetsnivået faller under terskelen. Noen potensielle feilkilder kan inkludere sensorens nøyaktighet, variasjoner i jordtype, og dreneringshastigheten til jorden. For å forbedre nøyaktigheten, kan man bruke flere sensorer plassert på ulike steder i jorden og gjennomsnittsberegne fuktighetsnivået. 

### Konklusjon
Prosjektet har demonstrert hvordan en mikrokontroller og jordfuktighetssensor kan brukes til å automatisere vanningsprosessen for planter. Ved å opprettholde optimale fuktighetsnivåer kan man forbedre plantehelsen og redusere vannforbruket. Muligheter for videreutvikling inkluderer bruk av flere sensorer og en mer avansert algoritme for vanning.

Dette prosjektet oppfyller kompetansemålene ved å utvikle og teste et funksjonelt produkt, analysere de innsamlede dataene, og reflektere over potensielle forbedringer.
