/*
 *  MoMEMta: a modular implementation of the Matrix Element Method
 *  Copyright (C) 2016  Universite catholique de Louvain (UCL), Belgium
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <momemta/ConfigurationSet.h>
#include <momemta/Module.h>
#include <momemta/Types.h>
#include <momemta/Utils.h>

class BlockB: public Module {
    public:
  
        BlockB(PoolPtr pool, const ConfigurationSet& parameters): Module(pool, parameters.getModuleName()) {
            
            sqrt_s = parameters.globalConfiguration().get<double>("energy");
            
            s12 = get<double>(parameters.get<InputTag>("s12"));
            
            m_particle_tags = parameters.get<std::vector<InputTag>>("inputs");
            for (auto& t: m_particle_tags)
              t.resolve(pool);
        }; 
  
        virtual void work() override {
      
            invisibles->clear();
            jacobians->clear();

            const LorentzVector& p2 = m_particle_tags[1].get<LorentzVector>();
            
            // FIXME
            const LorentzVector ISR; // = (*particles)[0];
            
            // pT = transverse total momentum of the visible particles
            // It will be used to reconstruct neutrinos, but we want to take into account the measured ISR (pt_isr = - pt_met - pt_vis),
            // so we add pt_isr to pt_vis in order to have pt_vis + pt_nu + pt_isr = 0 as it should be. 
            auto pT = p2 + ISR;


        
            invisibles->push_back({p1}); // Fixme
            jacobians->push_back(computeJacobian(p1, p2));
        

            
        }

    // The extra dimensions not present in the input
        virtual size_t dimensions() const override {
            return 0;
        }


        double computeJacobian(const LorentzVector& p1, const LorentzVector& p2) {
          
            const double E1  = p1.E();
            const double p1z = p1.Pz();

            const double E2  = p2.E();
            const double p2z = p2.Pz();
            // copied from Source/MadWeight/blocks/class_b.f
            
            
        }

    private:
        double sqrt_s;
  
        std::vector<InputTag> m_particle_tags;
        std::shared_ptr<std::vector<double>> jacobians = produce<std::vector<double>>("jacobians");

};
REGISTER_MODULE(BlockB);
