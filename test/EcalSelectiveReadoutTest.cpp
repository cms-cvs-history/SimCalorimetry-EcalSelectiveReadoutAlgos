#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DataFormats/EcalDigi/interface/EBDataFrame.h"
#include "DataFormats/EcalDigi/interface/EEDataFrame.h"
#include "DataFormats/EcalDigi/interface/EcalTriggerPrimitiveDigi.h"
#include "SimCalorimetry/EcalSelectiveReadoutAlgos/interface/EcalSelectiveReadoutSuppressor.h"
#include <vector>
#include<iostream>
#include<iterator>
using namespace std;
using namespace cms;

int main() {
  // start with the first little 5x5 block of crystals
  EBDetId barrelDet13(3, 3);
  //EEDetId endcapDet1(1,1,1);

  vector<DetId> barrelDetIds, endcapDetIds;
  barrelDetIds.push_back(barrelDet13);
  //endcapDetIds.push_back(endcapDet1);

  // make the digi collections
  EBDigiCollection barrelDigis;
  EEDigiCollection endcapDigis;
  EcalTrigPrimDigiCollection trigPrims;

 
  // middle crystal gets a high value
  EBDataFrame barrelDigi13(barrelDet13);
  barrelDigi13.setSize(10);
  barrelDigi13.setSample(5, EcalMGPASample(10*12, 2));
  barrelDigis.push_back(barrelDigi13);

  // trig prim
  EcalTrigTowerDetId towerDet(1, EcalBarrel, 2, 2);
  EcalTriggerPrimitiveDigi trigPrim(towerDet);
  trigPrim.setSize(10);
  trigPrim.setSample(5, EcalTriggerPrimitiveSample(20, true, 0) );
  trigPrims.push_back(trigPrim);

  // the suppressor
  EcalSelectiveReadoutSuppressor suppressor;
  suppressor.run(trigPrims, barrelDigis, endcapDigis);
  return 0;
}


