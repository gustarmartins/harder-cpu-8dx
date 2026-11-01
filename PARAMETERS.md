# Parameters — v0.2.1

[Exact tables](parameters.json) · [Every byte edit](parameter_edits.json)

## VLRA — AILevelTable

| Difficulty | Default | Minimum | Formation | CC additions |
|---|---:|---:|---:|---|
| Easy | 1.025 | 1 | 1 | 0, 0, 0, 0 |
| Normal | 1.025 | 1 | 1 | 0, 0, 0, 0 |
| Hard | 1.035 | 0.5 | 1 | 0, 0, 0, 0 |
| Expert | 1.01 | 0.5 | 1 | 0, 0, 0, 0 |

## MPRA — AIParamTable

| Field | Value |
|---|---|
| AddSpeedRatio_Up_ByFormation | 0.16 |
| AddSpeedRatio_Down_ByFormation | 0.12 |
| DisMin_CatchUp / DisMax_CatchUp | -3645.261 / 4860.3481 |
| DisMin_CatchDown / DisMax_CatchDown | 3645.261 / 18226.305 |

| Difficulty | CatchUp | CatchDown |
|---|---:|---:|
| Easy | 0 | 0 |
| Normal | 0 | 0 |
| Hard | 0.06 | -0.12 |
| Expert | 0.025 | -0.1 |

FormationSpan stores increments. Native construction accumulates and scales them into formation targets.

| Slot | Stored increment |
|---|---:|
| 00 | 0 |
| 01 | 495.1586 |
| 02 | 577.6849 |
| 03 | 660.2122 |
| 04 | 742.7363 |
| 05 | 825.2641 |
| 06 | 990.3203 |
| 07 | 1155.37 |
| 08 | 1320.4255 |
| 09 | 1485.4708 |
| 10 | 1650.5328 |
| 11 | 1815.5734 |

## FCRA — AIConfuseTable

Probability: **80%**. Trigger window: **35–90 racing seconds**.

| Difficulty | Scale minimum | Scale maximum |
|---|---:|---:|
| Easy | 1 | 1 |
| Normal | 1 | 1 |
| Hard | 0.25 | 0.5 |
| Expert | 0.05 | 0.3 |

## PIRA — AIItemTable

| Difficulty | Hold | Counter | Snipe |
|---|---:|---:|---:|
| Easy | 25 | 30 | 35 |
| Normal | 60 | 45 | 40 |
| Hard | 100 | 60 | 70 |
| Expert | 100 | 90 | 70 |

## PARA — AIProbability

- **RocketStart:** 100 across all four difficulty rows and twelve positions.

### {name}

- **Easy:** 0, 0, 0, 10, 10, 10, 20, 20, 30, 30, 30, 50.
- **Normal:** 0, 0, 0, 0, 0, 0, 10, 10, 20, 20, 30, 30.
- **Hard:** 0, 0, 0, 0, 0, 0, 0, 5, 8, 10, 12, 15.
- **Expert:** 0, 0, 0, 0, 0, 0, 0, 0, 5, 8, 10, 12.
- **Drift:** 100 across all four difficulty rows and twelve positions.
- **JumpAction:** 100 across all four difficulty rows and twelve positions.

## SCRA — AICourseTable

0 nonzero cells across 0 course rows.

## VIRA

The original table is preserved.

## Performance.bin — CPU mini-turbo targets

| Field | Original | Release |
|---|---:|---:|
| TMRP CPU blue | 250 | 100 |
| TMRP CPU orange | 660 | 396 |
| TMRP CPU purple | 1100 | 660 |

CPU row 20, offsets `0xCD0`, `0xCD4`, `0xCD8`. Native charging uses strict threshold comparisons.

The [director](README.md#race-director) uses these authored pace allowances and formation geometry during racing.
