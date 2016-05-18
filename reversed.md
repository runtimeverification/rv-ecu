# Windshield wiper
Primary CAN ID (Needs to be written on bus) - AF87110  
Secondary CAN ID (Unsure of its purpose) - AF81111  
Primary DLC - 3  
Secondary DLC - 2  

| Action    | Primary Data | Secondary Data |
|-----------|--------------|----------------|
| No motion | 00 00 00     | 08 00          |
| Pulse     | 02 00 00     | 28 00          |
| Low freq  | 40 00 00     | 28 00          |
| Med freq  | 10 00 00     | 28 00          |
| High freq | 04 00 00     | 28 00          |

# Headlights
Primary CAN ID - AF87010  
Secondary CAN ID - AF81111  
DLC - 2 for both  

| Action             | Primary Data  | Secondary Data |
|--------------------|---------------|----------------|
| Off                | 00 00         | 08 00          |
| Pull               | 02 00         | 01 00          |
| low (notch one)    | 40 00         | 48 48          | 
| auto (notch two)   | 10 04         | 42 48          |
| high (notch three) | 50 00         | 42 48          |

# Left rear door
This one requires sending a cycle of commands  
CAN ID - EF81296  
DLC - 1  
Messages: Send C2, then C3  

# Key lock/unlock button
CAN ID - EF81296  
DLC - 1  
Lock: 01  
Unlock: 02  
