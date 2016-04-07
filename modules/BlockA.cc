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

class BlockA: public Module {
    public:
  
        BlockA(PoolPtr pool, const ConfigurationSet& parameters): Module(pool, parameters.getModuleName()) {
            sqrt_s = parameters.globalConfiguration().get<double>("energy");
            
            m_particle_tags = parameters.get<std::vector<InputTag>>("inputs");
            for (auto& t: m_particle_tags)
              t.resolve(pool);
        }; 
  
        virtual void work() override {
      
            invisibles->clear();
            jacobians->clear();

            const LorentzVector& p1 = m_particle_tags[0].get<LorentzVector>();
            const LorentzVector& p2 = m_particle_tags[1].get<LorentzVector>();
            
            
            



        
            invisibles->push_back({xxx}); // Fixme
            jacobians->push_back(computeJacobian(p1, p2));
        

            
        }

    // The extra dimensions not present in the input
        virtual size_t dimensions() const override {
            return 2;
        }


        double computeJacobian(const LorentzVector& p1, const LorentzVector& p2) {
          

            
            // copied from Source/MadWeight/blocks/class_a.f
            
            
        }

    private:
        double sqrt_s;
  
        std::vector<InputTag> m_particle_tags;
        std::shared_ptr<std::vector<double>> jacobians = produce<std::vector<double>>("jacobians");

};
REGISTER_MODULE(BlockA);
