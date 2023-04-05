
#include <libraries/catch/catch.hpp>
#include <data-units/DataType.hpp>
#include <utilities/MPRDispatcher.hpp>


using namespace std;
using namespace mpr::precision;


template <typename T>
void
CheckValues(DataType *apData, char *apValidator) {

    T *temp_data = (T *) apData->GetData();
    T *temp_validate = (T *) apValidator;
    auto size = apData->GetSize();
    for (auto i = 0; i < size; i++) {
        REQUIRE(temp_data[ i ] == temp_validate[ i ]);
    }
}


template <typename T>
void
InitValidator(char *&apData, size_t aSize) {
    T *temp = new T[aSize];
    for (auto i = 0; i < aSize; i++) {
        temp[ i ] = (T) 1.5;
    }
    apData = (char *) temp;
}


void
TEST_DATA_TYPE() {

    SECTION("Test Initialization") {
        cout << "Testing MPR CLASS ..." << endl;

        DataType a(50, "float");
        REQUIRE(a.GetSize() == 50);
        REQUIRE(a.IsMatrix() == false);
        REQUIRE(a.GetDimensions() == nullptr);

        char *validator;
        Precision temp_precision = FLOAT;
        SIMPLE_DISPATCH(temp_precision, InitValidator, validator, 50)
        SIMPLE_DISPATCH(temp_precision, CheckValues, &a, validator)

        a.ToMatrix(5, 10);
        REQUIRE(a.GetSize() == 50);
        REQUIRE(a.IsMatrix() == true);
        REQUIRE(a.GetDimensions()->GetNRow() == 5);
        REQUIRE(a.GetDimensions()->GetNCol() == 10);

        a.ToVector();
        REQUIRE(a.IsMatrix() == false);
        REQUIRE(a.GetSize() == 50);
        REQUIRE(a.GetDimensions() == nullptr);

        delete[] validator;
    }SECTION("Test Setter and Getter") {
        DataType a(50, "double");
        char *validator;
        Precision temp_precision = DOUBLE;
        SIMPLE_DISPATCH(temp_precision, InitValidator, validator, 50)
        auto data = (double *) validator;
        auto size = a.GetSize();
        for (auto i = 0; i < size; i++) {
            REQUIRE(data[ i ] == a.GetVal(i));
        }

        for (auto i = 0; i < size; i++) {
            a.SetVal(i, 3.555555555);
        }

        for (auto i = 0; i < size; i++) {
            REQUIRE(a.GetVal(i) == 3.555555555);
        }

        DataType b(50, "float");

        SECTION("Test Copy Constructor") {
            DataType c = b;

            REQUIRE(c.GetSize() == 50);
            REQUIRE(c.IsMatrix() == false);
            REQUIRE(c.GetDimensions() == nullptr);

            for (auto i = 0; i < size; i++) {
                c.SetVal(i, 3.225);
            }
            for (auto i = 0; i < size; i++) {
                REQUIRE(b.GetVal(i) != c.GetVal(i));
            }

        }
        delete[] validator;
    }

    SECTION("Test Clear Up") {
        DataType temp(30, 1);
        REQUIRE(temp.GetPrecision() == HALF);

        temp.ClearUp();
        REQUIRE(temp.GetData() == nullptr);
        REQUIRE(temp.GetDimensions() == nullptr);

    }SECTION("Test Precision Conversion") {

        cout << "Testing Precision Conversion ..." << endl;

        DataType a(35, "float");
        auto pData_in_a = (float *) a.GetData();
        auto size_a = a.GetSize();

        for (auto i = 0; i < size_a; i++) {
            pData_in_a[ i ] = i;
        }

        a.ConvertPrecision(DOUBLE);
        REQUIRE(a.GetSize() == size_a);
        REQUIRE(a.GetPrecision() == DOUBLE);

        auto pData_in_a_new = (double *) a.GetData();
        for (auto i = 0; i < size_a; i++) {
            REQUIRE(pData_in_a_new[ i ] == i);
            pData_in_a_new[ i ] = 1.5;
        }

        a.ConvertPrecision(HALF);

        REQUIRE(a.GetSize() == size_a);
        REQUIRE(a.GetPrecision() == HALF);

        auto pData_in_a_new_int = (int *) a.GetData();
        for (auto i = 0; i < size_a; i++) {
            REQUIRE(pData_in_a_new_int[ i ] == 1);

        }

    }SECTION("Converter") {

        cout << "Testing NumericVector Conversion ..." << endl;

        DataType a(50, FLOAT);
        auto pData_in_a = (float *) a.GetData();
        auto size_a = a.GetSize();

        for (auto i = 0; i < size_a; i++) {
            pData_in_a[ i ] = i;
        }

        size_t i = 0;
        auto pOutput_vector = a.ConvertToNumericVector();
        for (auto x: *pOutput_vector) {
            REQUIRE(x == i);
            i++;
        }

        delete pOutput_vector;

    }SECTION("Test Copy Constructor for different precision"){
        vector<double> vals(50,5);
        DataType a(vals,DOUBLE);
        DataType b(a,FLOAT);

        REQUIRE(b.GetPrecision()==FLOAT);
        REQUIRE(b.GetSize()==50);

        for(auto i=0;i<b.GetSize();i++){
            REQUIRE(b.GetVal(i)==5);
        }
    }


}


TEST_CASE("DataTypeTest", "[DataType]") {
    TEST_DATA_TYPE();
}
