This project simulates the generation and decay of elementary particles following collisions of subatomic objects.
In particular, among pions, kaons, protons and electorns, K* particles are generated. While the first ones are stable, 
the last one rapidly decays in equal proportions into a positive kaon and a negative pion, or a negative kaon and a positive pion.

The aim of the program is to detect the K* decay from the distributions of invariant masses of all particles. 
In particular, since the decay of K* produces pions and kaons of opposite charge, by analysing the distribution of invariant masses 
of all possible couples of particles with same charge and the distribution of the distribution of invariant masses of all possible couples 
of particles with opposite charge, one can subtract the second from the first one and retrieve the distribution of invariant masses 
the distribution of invariant masses of all couples of particles generated  by the decay.
The same reasoning is repeated considering only pions and kaons in order to get more precise data.

Particles are generated in predefined proportions, with momentum distributed according to an exponential distribution and polar and azimuthal angle
according to uniform distributions. 

`main_gen.C` (`main.cpp` if you prefer to compile not in root environment) program simulates the decay and shows useful distributions, `analize_histo.C`, 
instead, is a ROOT macro that analyzes the data acquired via histograms and fits, printis data on terminal and draws histograms.

This project relies on _ROOT Data Analysis Framework_ developed by CERN. You need to install it in order to execute the simulation.
Code is written in c++ and uses root libraries to create histograms and analyze data.

To compile and run the program you have two ways...

* External compilation
  ```console
    user@user:~$ g++ -Wall -Wextra -o decay.exe particleType.cpp resonanceType.cpp particle.cpp main.cpp `root-config --cflags --libs`
    user@user:~$ ./decay.exe
  ```

  To analyze the data with root
  ```console
    user@user:~$ root
    user@user:~$ .L analyze_histos.C
    user@user:~$ analyze_histos()
  ```

* Internal compilation in root environment (recommended)
  ```console
    user@user:~$ root
    user@user:~$ .L particleType.cxx+
    user@user:~$ .L resonanceType.cxx+
    user@user:~$ .L particle.cxx+
    user@user:~$ .L main_gen.C+
    user@user:~$ main_gen()
  ```

  To analyze the data with root
  ```console
    user@user:~$  root 
    user@user:~$ .L analyze_histos.C 
    user@user:~$ analyze_histos() 
  ```

Last but not least, the program has been developed by Matteo Mirabelli, Riccardo Pagnoni, Andrea Maria Varisano and
Alberto Zaghini for _Laboratiorio di Elettromagnetismo e Ottica, OOP and Root_ module.
To get more information about the project, please read the report.

