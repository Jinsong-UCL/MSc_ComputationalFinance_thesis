//
// Created by Marco Paggiaro on 11/01/2021.
//

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <iterator>
#include "Calibration.h"
#include "utility.h"
//#include <boost/math/quadrature/gauss.hpp>

Calibration::Calibration(const std::vector<double> &strikes,
                         const std::vector<double> &maturities,
                         const double *parameters, unsigned nParameters, double r,  double S0,
                         double q ): nParameters((int)nParameters)
{
    opts.resize(LM_OPTS_SZ), info.resize(LM_INFO_SZ);
    opts[0] = 1e-5; //LM_INIT_MU;
    // stopping thresholds for
    opts[1] = 1E-10;       // ||J^T e||_inf
    opts[2] = 1E-10;       // ||Dp||_2
    opts[3] = 1E-10;       // ||e||_2
    opts[4] = LM_DIFF_DELTA; // finite difference if used

    // First, we get the parameters of the market:
    auto v0 = parameters[0],
        theta = parameters[1],
        rho = parameters[2],
        kappa = parameters[3],
        sigma = parameters[4];

    // Save original market parameters:
    marketParameters.resize(nParameters);
    for (int i = 0; i < marketParameters.size(); ++i)
        marketParameters[i] = parameters[i];

    // Then, we save the information in the options:
    SPX_options.reserve(strikes.size());
    for (unsigned i = 0; i < strikes.size(); ++i)
        SPX_options.emplace_back(strikes[i], maturities[i],r,
                                 kappa,theta, sigma, rho, v0, S0, "C", nParameters);
}

Calibration::Calibration(const std::vector<double> &SPX_strikes, const std::vector<double> &SPX_maturities,
                         const std::vector<double> &VIX_strikes, const std::vector<double> &VIX_maturities,
                         double *parameters, unsigned int nParameters,
                         double r, double S0, bool displacementFlag, double q
                         ) :
        Calibration(SPX_strikes, SPX_maturities, parameters, nParameters,r, S0, q)
{
    // First, we get the parameters of the market:
    auto v0 = parameters[0],
            theta = parameters[1],
            rho = parameters[2],
            kappa = parameters[3],
            sigma = parameters[4];
    VIX_options.reserve(VIX_strikes.size());
    for (unsigned i = 0; i < VIX_strikes.size(); ++i)
        VIX_options.emplace_back(VIX_strikes[i], VIX_maturities[i],
                                 r,kappa,theta, sigma, rho, v0, S0, "C", nParameters);

    if (displacementFlag)
    {
        setTermStructure(SPX_maturities, VIX_maturities);
        if (optionExpiries.size() - 1 != marketParameters.size() - 5)
            std::cout << "Wrong length of parameter number! Expected calibration errors." << std::endl;

        // Now we are ready to set the indices for the computation of the integrals:
        for (auto & SPX_option : SPX_options)
        {
            SPX_option.setDisplacement(parameters,optionExpiries,deltaTimes);
            SPX_option.SetIndexT();
        }

        for (auto & VIX_option : VIX_options)
        {
            VIX_option.setDisplacement(parameters,optionExpiries,deltaTimes);
            VIX_option.SetIndexT();
            VIX_option.SetIndexTPlusTau();
        }
    }
}

Calibration::Calibration(const std::vector<double> &SPX_strikes, const std::vector<double> &SPX_maturities,
                         const std::vector<double> &SPX_mkt_prices, const std::vector<double> &SPX_rates,
                         const std::vector<double> &VIX_strikes, const std::vector<double> &VIX_maturities,
                         const std::vector<double> &VIX_mkt_prices, const std::vector<double> &VIX_rates,
                         const std::vector<std::string> &SPX_option_types, double S0, double VIX_0,
                         bool displacementFlag, double q)
{
    // get settings for calibration:
    opts.resize(LM_OPTS_SZ), info.resize(LM_INFO_SZ);
    opts[0] = LM_INIT_MU;
    // stopping thresholds for
    opts[1] = 1E-10;       // ||J^T e||_inf
    opts[2] = 1E-10;       // ||Dp||_2
    opts[3] = 1E-8;       // ||e||_2
    opts[4] = LM_DIFF_DELTA; // finite difference if used

    // save market prices:
    marketPrices = SPX_mkt_prices;
    marketPrices.insert(marketPrices.end(),VIX_mkt_prices.begin(), VIX_mkt_prices.end());

    // get info on the term structure:
    setTermStructure(SPX_maturities, VIX_maturities);

    if (displacementFlag)
        nParameters = 5 + deltaTimes.size();
    else
        nParameters = 5;

    // create the options:
    SPX_options.reserve(SPX_strikes.size());
    VIX_options.reserve(VIX_strikes.size());

    for (int i = 0; i < SPX_strikes.size(); ++i)
    {
        SPX_options.emplace_back(SPX_strikes[i], SPX_maturities[i], SPX_rates[i], S0, SPX_option_types[i],
                                 nParameters, q);
        SPX_options.back().setDisplacement(nullptr,optionExpiries,deltaTimes);
        SPX_options.back().SetIndexT();
    }

    for (int i = 0; i < VIX_strikes.size(); ++i) {
        VIX_options.emplace_back(VIX_strikes[i], VIX_maturities[i], VIX_rates[i], VIX_0, "C",
                                 nParameters, q);
        VIX_options.back().setDisplacement(nullptr,optionExpiries,deltaTimes);
        VIX_options.back().SetIndexT();
        VIX_options.back().SetIndexTPlusTau();
    }
    // what about initial parameters? we set them to zero (for now).
    marketParameters.resize(nParameters);
}

void Calibration::setParameters(const double *parameters)
{
    for (auto &option : SPX_options)
        option.setParameters(parameters);

    for (auto &option : VIX_options)
        option.setParameters(parameters);
}

unsigned Calibration::size() const
{
    return SPX_options.size() + VIX_options.size();
}

std::vector<double> Calibration::SPX_Prices() const
{
    std::vector<double> prices(SPX_options.size());
    for (int i = 0; i < SPX_options.size(); ++i)
    {
        prices[i] = SPX_options[i].Price();
    }
    return prices;
}

std::vector<double> Calibration::VIX_Prices() const
{
    std::vector<double> prices(VIX_options.size());
    for (int i = 0; i < VIX_options.size(); ++i)
    {
        prices[i] = VIX_options[i].Price();
    }
    return prices;
}

std::vector<double> Calibration::Prices() const
{
    auto prices = SPX_Prices(), VIX_prices = VIX_Prices();
    prices.insert(prices.end(), VIX_prices.begin(), VIX_prices.end());
    return prices;
}

std::vector<double> Calibration::SPX_Gradients() const
{
    std::vector<double> gradients;
    gradients.reserve( SPX_options.size() * marketParameters.size());
    for (const auto & SPX_option : SPX_options)
    {
        auto currentGradient = SPX_option.Jacobian();
        gradients.insert(gradients.end(), currentGradient.begin(), currentGradient.end());
    }
    return gradients;
}

std::vector<double> Calibration::VIX_Gradients() const
{
    std::vector<double> gradients;
    gradients.reserve( VIX_options.size() * marketParameters.size());
    for (const auto & VIX_option : VIX_options)
    {
        auto currentGradient = VIX_option.Jacobian();
        gradients.insert(gradients.end(), currentGradient.begin(), currentGradient.end());
    }
    return gradients;
}

std::vector<double> Calibration::Gradients() const
{
    auto gradients = SPX_Gradients(), VIX_gradients = VIX_Gradients();
    gradients.insert(gradients.end(), VIX_gradients.begin(), VIX_gradients.end());
    return gradients;
}

void Calibration::saveCalibration(const double *parameters, const double *information)
{
    // Save calibration results:
    for (int i = 0; i < info.size(); ++i) {
        info[i] = information[i];
    }
    searchParameters.resize(marketParameters.size());
    for (int i = 0; i < searchParameters.size(); ++i) {
        searchParameters[i] = parameters[i];
    }
    calibratedPrices = Prices();
}

void Calibration::print(const double *initialGuess) const
{
    std::cout << "-------- -------- -------- Heston Model Calibrator -------- -------- --------" << std::endl;
    // To be continued ...
    // values for controlling format
    const int column_width = 16;
    const int num_fields = 4;
    const std::string sep = " |" ;
    const int total_width = num_fields * column_width + sep.size() * num_fields ;
    const std::string line = sep + std::string( total_width-1, '-' ) + '|' ;

    std::vector<std::string> parameterNames(searchParameters.size(), "phi");
    parameterNames[0] = "v0", parameterNames[1] = "theta", parameterNames[2] = "rho",
    parameterNames[3] = "kappa", parameterNames[4] = "sigma";
    if (searchParameters.size() > 5)
        for (int i = 5; i < searchParameters.size(); ++i)
        {
            parameterNames[i] += std::to_string(i - 5);
        }
    // First, print names of columns:
    std::cout << line << '\n' << sep
              << std::setw(column_width) << "Parameter:" << sep
              << std::setw(column_width) << "Initial value:" << sep
              << std::setw(column_width) << "Optimum found:" << sep
              << std::setw(column_width) << "Real optimum:" << sep << '\n' << line << '\n' ;

    for (int i = 0; i < searchParameters.size(); ++i)
    {
        std::cout << sep << std::setw(column_width) << parameterNames[i]
                  << std::scientific << std::setprecision(8)
                  << sep << std::setw(column_width) << initialGuess[i]
                  << sep << std::setw(column_width) << searchParameters[i]
                  << sep << std::setw(column_width) << (!marketParameters.empty() ? marketParameters[i] : 0)
                  << sep << '\n';
    }
    std::cout << line << '\n';

    if (int(info[6]) == 6) {
        std::cout << "Solved: stopped by small ||e||_2 = "<< info[1] << " < " << opts[3]<< std::endl;
    } else if (int(info[6]) == 1) {
        std::cout << "Solved: stopped by small gradient J^T e = " << info[2] << " < " << opts[1]<< std::endl;
    } else if (int(info[6]) == 2) {
        std::cout << "Solved: stopped by small change Dp = " << info[3] << " < " << opts[2]<< std::endl;
    } else if (int(info[6]) == 3) {
        std::cout << "Unsolved: stopped by it_max " << std::endl;
    } else if (int(info[6]) == 4) {
        std::cout << "Unsolved: singular matrix. Restart from current p with increased mu"<< std::endl;
    } else if (int(info[6]) == 5) {
        std::cout << "Unsolved: no further error reduction is possible. Restart with increased mu"<< std::endl;
    } else if (int(info[6]) == 7) {
        std::cout << "Unsolved: stopped by invalid values, user error"<< std::endl;
    }

    std::cout << "-------- -------- -------- Computational cost -------- -------- --------" << std::endl;
    std::cout << "          Time cost: " << double(stopClock - startClock) / CLOCKS_PER_SEC << " seconds " << std::endl;
    std::cout << "       # iterations: " << int(info[5]) << std::endl;
    std::cout << "# price evaluations: " << int(info[7]) << std::endl;
    std::cout << " # Jac. evaluations: " << int(info[8]) << std::endl;
    std::cout << "# of lin sys solved: " << int(info[9]) << std::endl; //The attempts to reduce error
    std::cout << "-------- -------- -------- Residuals -------- -------- --------" << std::endl;
    std::cout << "          ||e0||_2: " << info[0] << std::endl;
    std::cout << "          ||e*||_2: " << info[1] << std::endl;
    std::cout << "       ||J'e||_inf: " << info[2] << std::endl;
    std::cout << "          ||Dp||_2: " << info[3] << std::endl;
}

//std::vector<double> Calibration::IntegralDisplacement()
//{
//    std::vector<double> intPhi(EuropeanOption::deltaTimes.size());
//    intPhi[0] = EuropeanOption::deltaTimes[0] * EuropeanOption::phiT[0];
//    for (int i = 1; i < intPhi.size(); ++i)
//    {
//        intPhi[i] = intPhi[i-1] + EuropeanOption::deltaTimes[i] * EuropeanOption::phiT[i];
//    }
//
//    return intPhi;
//}

//void Calibration::setMarketPrices()
//{
//    marketPrices = Prices();
//}

void Calibration::setMarketParameters(const double *parameters)
{
    if (!marketParameters.empty())
        for (int i = 0; i < marketParameters.size(); ++i)
        {
            marketParameters[i] = parameters[i];
        }
    setParameters(parameters);
    // compute target market prices:
    marketPrices = Prices();
}

void
Calibration::setTermStructure(const std::vector<double> &SPX_maturities, const std::vector<double> &VIX_maturities)
{
    auto SPX_t(SPX_maturities), VIX_t(VIX_maturities);
    SPX_t.push_back(0.0);
    std::sort(SPX_t.begin(), SPX_t.end());
    SPX_t.erase(std::unique(SPX_t.begin(), SPX_t.end()), SPX_t.end());
    std::sort(VIX_t.begin(), VIX_t.end());
    VIX_t.erase(std::unique(VIX_t.begin(), VIX_t.end()), VIX_t.end());
    std::vector<double> partialT(SPX_t.size() + VIX_t.size());
    auto it = std::set_union(SPX_t.begin(), SPX_t.end(),
                             VIX_t.begin(), VIX_t.end(), partialT.begin());
    partialT.resize(it - partialT.begin());

    auto VIX_tauBar(VIX_t);
    for (double &i : VIX_tauBar)
    {
        i += EuropeanOption::tau_bar;
    }

    std::vector<double> finalT(partialT.size() + VIX_tauBar.size());
    // unite also B + tau_bar:
    auto it2 = std::set_union(partialT.begin(), partialT.end(), VIX_tauBar.begin(),
                              VIX_tauBar.end(), finalT.begin());
    finalT.resize(it2 - finalT.begin());

    // We need to implement a function that compares two very similar doubles:
    std::vector<int> areSame;
    for (int i = 0; i < finalT.size() - 1; ++i)
    {
        if (AreSame(finalT[i], finalT[i + 1]))
            areSame.push_back(i);
    }
    for (int i : areSame)
    {
        finalT.erase(finalT.begin() + i);
    }

    // compute differences:
    std::vector<double> deltaT(finalT.size() - 1);
    for (int i = 0; i < deltaT.size(); ++i)
    {
        deltaT[i] = finalT[i + 1] - finalT[i];
    }
    optionExpiries = finalT;
    deltaTimes = deltaT;
}




//void computePrices(double *parameters, double *prices, int m, int n, void *data)
//{
//    // unused variables (however needed for levmar):
//    (void) m;
//    (void) n;
//
//    auto *calibration = static_cast<Calibration *> (data);
//    // update market parameters:
//    calibration->setParameters(parameters);
//    // compute prices:
//    auto modelPrices = calibration->Prices();
//    // save them in the array:
//    for (int i = 0; i < modelPrices.size(); ++i)
//    {
//        prices[i] = modelPrices[i];
//    }
//}

void objectiveFunction(double *parameters, double *objectiveFunction, int m, int n, void *data)
{
    // unused variables (however needed for levmar):
    (void) m;
    (void) n;

    auto *calibration = static_cast<Calibration *> (data);
    // update market parameters:
    calibration->setParameters(parameters);
    // compute prices:
    auto modelPrices = calibration->Prices();
    // save them in the array:
    auto nSPX = calibration->SPX_options.size(),
            nVIX = calibration->VIX_options.size();
    int nOptions;
    for (int i = 0; i < modelPrices.size(); ++i)
    {
        if (i < nSPX * calibration->nParameters)
            nOptions = nSPX;
        else
            nOptions = nVIX;
        objectiveFunction[i] = (modelPrices[i] - calibration->marketPrices[i]) /
                    (sqrt(2 * nOptions) * calibration->marketPrices[i]);
    }
}

//void perturbPrices(double *prices, int size)
//{
//    std::default_random_engine generator;
//    std::normal_distribution<double> distribution(0.0, 1e-4);
//    for (int i = 0; i < size; ++i)
//    {
//        // Perturb prices:
//        prices[i] += distribution(generator) * prices[i];
//    }
//}

//void computeGradients(double *parameters, double *gradient, int m, int n, void *data)
//{
//    // unused variables (however needed for Levmar):
//    (void) m;
//    (void) n;
//
//    auto *calibration = static_cast<Calibration *> (data);
//    // update market parameters:
//    calibration->setParameters(parameters);
//    // compute gradients:
//    auto modelGradient = calibration->Gradients();
//    // place them inside the array:
//    for (int i = 0; i < modelGradient.size(); ++i)
//        gradient[i] = modelGradient[i];
//}

void gradientObjective(double *parameters, double *gradient, int m, int n, void *data)
{
    // unused variables (however needed for Levmar):
    (void) m;
    (void) n;

    auto *calibration = static_cast<Calibration *> (data);
    // update market parameters:
    calibration->setParameters(parameters);
    // compute gradients:
    auto modelGradient = calibration->Gradients();
    // place them inside the array:
    auto nSPX = calibration->SPX_options.size(),
            nVIX = calibration->VIX_options.size();
    for (int i = 0; i < modelGradient.size(); ++i) {
        int nOptions;
        if (i < nSPX * calibration->nParameters)
            nOptions = nSPX;
        else
            nOptions = nVIX;
        gradient[i] = modelGradient[i] / (sqrt(2 * nOptions)
                * calibration->marketPrices[i / calibration->nParameters]);
    }
}

void calibrate(Calibration &calibration, const double *initialGuess, int maxIterations,
               const bool perturbation, const std::string &gradientType)
{
    // Save the "original" market parameters:
    double marketParameters[calibration.marketParameters.size()];
    for (int i = 0; i < calibration.marketParameters.size(); ++i) {
        marketParameters[i] = calibration.marketParameters[i];
    }
    // Compute market prices:
    calibration.marketPrices = calibration.Prices();

//    if (perturbation)
//        perturbPrices(marketPrices, (int) calibration.size());

    // algorithm parameters:
    // int itMax = 35;
    double opts[LM_OPTS_SZ], info[LM_INFO_SZ];
    for (int i = 0; i < calibration.opts.size(); ++i)
    {
        opts[i] = calibration.opts[i];
    }
    // >>> Enter calibrating routine >>>
    calibration.startClock = clock();

    // Search parameters:
    double p[calibration.marketParameters.size()];
    // Set initial guess:
    for (int i = 0; i < calibration.marketParameters.size(); ++i)
        p[i] = initialGuess[i];

    // debug: check if gradient is correct:
//    double checker[calibration.size()];
//    std::fill_n(checker, calibration.size(), -1);
//    dlevmar_chkjac(computePrices, computeGradients, p, (int) calibration.marketParameters.size(),
//                   (int) calibration.size(), (void *) &calibration, checker);
//    // double obFun[calibration.size()], jacFun[calibration.size() * EuropeanOption::nParameters];

    // Perform calibration with Levenberg-Marquardt algorithm:

    // Constraints: non-negative displacement.
    double upperBound[calibration.marketParameters.size()], lowerBound[calibration.marketParameters.size()];
    // no upper bound:
    std::fill_n(upperBound, calibration.marketParameters.size(), std::numeric_limits<double>::max());
    std::fill_n(lowerBound, calibration.marketParameters.size(), 0);
    for (int i = 0; i < calibration.marketParameters.size(); ++i)
    // upper and lower bound for correlation:
    lowerBound[2] = -1; upperBound[2] = 1;

    if (gradientType == "Analytical")
        dlevmar_bc_der(objectiveFunction, gradientObjective, p, nullptr, (int) calibration.marketParameters.size(),
                       (int) calibration.size(),
                       lowerBound, upperBound, nullptr, maxIterations, opts, info, nullptr, nullptr,
                       (void *) &calibration);

    else // numerical gradient:
        dlevmar_bc_dif(objectiveFunction, p, nullptr, (int) calibration.marketParameters.size(),
                       (int) calibration.size(),
                       lowerBound, upperBound, nullptr, maxIterations, opts, info, nullptr, nullptr, (void *) &calibration);

    calibration.stopClock = clock();
    // save calibration results:
    calibration.saveCalibration(p, info);
    // reset market parameters back to start:
    calibration.setParameters(marketParameters);
    // Print calibration result:
    calibration.print(initialGuess);
}

void calibrateMarketData (Calibration &calibration, const double *initialGuess, bool perturbation,
                          const std::string &gradientType)
{
    // algorithm parameters:
    int itMax = 100;
    double opts[LM_OPTS_SZ], info[LM_INFO_SZ];
    for (int i = 0; i < calibration.opts.size(); ++i)
    {
        opts[i] = calibration.opts[i];
    }
    // >>> Enter calibrating routine >>>
    calibration.startClock = clock();

    // Search parameters:
    double p[calibration.nParameters];
    // Set initial guess:
    for (int i = 0; i < calibration.nParameters; ++i)
        p[i] = initialGuess[i];

    // Perform calibration with Levenberg-Marquardt algorithm:

    // Constraints: non-negative displacement.
    double upperBound[calibration.nParameters], lowerBound[calibration.nParameters];
    // no upper bound:
    std::fill_n(upperBound, calibration.nParameters, std::numeric_limits<double>::max());
    std::fill_n(lowerBound, calibration.nParameters, 0);

    // upper and lower bound for correlation:
    lowerBound[2] = -1; upperBound[2] = 1;
    // kappa cannot be exactly zero:
    lowerBound[0] = lowerBound[1] = lowerBound[3] = lowerBound[4] = 1e-4;

    if (gradientType == "Analytical")
        dlevmar_bc_der(objectiveFunction, gradientObjective, p, nullptr, (int) calibration.nParameters,
                       (int) calibration.size(),
                       lowerBound, upperBound, nullptr, itMax, opts, info, nullptr, nullptr,
                       (void *) &calibration);

    else // numerical gradient:
        dlevmar_bc_dif(objectiveFunction, p, nullptr, (int) calibration.nParameters,
                       (int) calibration.size(),
                       lowerBound, upperBound, nullptr, itMax, opts, info, nullptr, nullptr, (void *) &calibration);

    calibration.stopClock = clock();
    // save calibration results:
    calibration.saveCalibration(p, info);
    // Print calibration result:
    calibration.print(initialGuess);
}

void testModel (Calibration &calibration, int nIterations, const std::string &gradientType)
{
    int countSuccessfulCalibrations = 0;

    int countWrongMinimaFound = 0;

    double marketParameters[calibration.marketParameters.size()],
        initialGuess[calibration.marketParameters.size()];
    for (int i = 0; i < nIterations; ++i)
    {
        // Generate initial guess and market parameters
        generateGuess(marketParameters, (int) calibration.marketParameters.size());
        generateGuess(initialGuess, (int) calibration.marketParameters.size());

        std::cout << "Simulation " << i+1 << " of " << nIterations << "." << std::endl;
        // Calibrate
        calibration.setMarketParameters(marketParameters);
        calibrate(calibration, initialGuess, 35, false, gradientType);

        while (calibration.info[6] == 7 or calibration.info[6] == 3)
        {
            countWrongMinimaFound ++;
            // slow convergence: let's change initial guess.
            std::cout << "Possible local minimum. Let's change initial point." << std::endl;
            generateGuess(initialGuess, (int) calibration.marketParameters.size());
            calibrate(calibration, initialGuess, 35, false, gradientType);
        }

        // See if the calibration was successful.
        if (calibration.info[6] == 6)
            countSuccessfulCalibrations++;
    }
    std::cout << countSuccessfulCalibrations << " successful calibrations out of "
              << nIterations << " simulations." << std::endl;

    std::cout << "Initial point changed " << countWrongMinimaFound << " times." <<std::endl;
}

void generateGuess(double *parameters, int size)
{
    // Objects for generating random numbers:
    std::random_device randomDevice;
    std::default_random_engine generator{randomDevice()};
    std::uniform_real_distribution<double> uniform(0.0, 1.0);
    // Generate guess:
    for (int j = 0; j < size; ++j)
    {
        if (j <= 1 or j == 4)
            parameters[j] = 0.05 + 0.9 * uniform(generator);
        else if (j == 2)
            parameters[j] = -0.1 - 0.8 * uniform(generator);
        else if (j == 3)
            parameters[j] = 0.5 + 4.5 * uniform(generator);
        else // displacement vector:
        {

            parameters[j] = 8e-4 * uniform(generator);


        }
    }
}