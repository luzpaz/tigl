/* 
* Copyright (C) 2007-2013 German Aerospace Center (DLR/SC)
*
* Created: 2012-10-17 Martin Siggel <Martin.Siggel@dlr.de>
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
/**
* @file
* @brief Tests for testing behavior of wing component segment functions.
*/

#include "test.h" // Brings in the GTest framework
#include "tigl.h"

#include "CCPACSConfigurationManager.h"
#include "CCPACSWing.h"
#include "CCPACSWingComponentSegment.h"
#include "CCPACSWingSegment.h"
#include "CCPACSMaterialDefinition.h"
#include "CTiglWingChordface.h"

/******************************************************************************/

class WingComponentSegment : public ::testing::Test
{
protected:
    static void SetUpTestCase()
    {
        const char* filename = "TestData/CPACS_30_D150.xml";
        ReturnCode tixiRet;
        TiglReturnCode tiglRet;

        tiglHandle = -1;
        tixiHandle = -1;
        
        tixiRet = tixiOpenDocument(filename, &tixiHandle);
        ASSERT_TRUE (tixiRet == SUCCESS);
        tiglRet = tiglOpenCPACSConfiguration(tixiHandle, "D150_VAMP", &tiglHandle);
        ASSERT_TRUE(tiglRet == TIGL_SUCCESS);
    }

    static void TearDownTestCase()
    {
        ASSERT_TRUE(tiglCloseCPACSConfiguration(tiglHandle) == TIGL_SUCCESS);
        ASSERT_TRUE(tixiCloseDocument(tixiHandle) == SUCCESS);
        tiglHandle = -1;
        tixiHandle = -1;
    }

    void SetUp() override {}
    void TearDown() override {}


    static TixiDocumentHandle           tixiHandle;
    static TiglCPACSConfigurationHandle tiglHandle;
};

class WingComponentSegment2 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        const char* filename = "TestData/CPACS_30_D250_10.xml";
        ReturnCode tixiRet;
        TiglReturnCode tiglRet;

        tiglHandle = -1;
        tixiHandle = -1;
        
        tixiRet = tixiOpenDocument(filename, &tixiHandle);
        ASSERT_EQ (SUCCESS, tixiRet);
        tiglRet = tiglOpenCPACSConfiguration(tixiHandle, "D250_VAMP", &tiglHandle);
        ASSERT_EQ(TIGL_SUCCESS, tiglRet);
    }

    void TearDown() override
    {
        ASSERT_EQ(TIGL_SUCCESS, tiglCloseCPACSConfiguration(tiglHandle));
        ASSERT_EQ(SUCCESS, tixiCloseDocument(tixiHandle));
        tiglHandle = -1;
        tixiHandle = -1;
    }

    TixiDocumentHandle           tixiHandle;
    TiglCPACSConfigurationHandle tiglHandle;
};


class WingComponentSegment3 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        const char* filename = "TestData/D150_v30.xml";
        ReturnCode tixiRet;
        TiglReturnCode tiglRet;

        tiglHandle = -1;
        tixiHandle = -1;
        
        tixiRet = tixiOpenDocument(filename, &tixiHandle);
        ASSERT_EQ (SUCCESS, tixiRet);
        tiglRet = tiglOpenCPACSConfiguration(tixiHandle, "D150modelID", &tiglHandle);
        ASSERT_EQ(TIGL_SUCCESS, tiglRet);
    }

    void TearDown() override
    {
        ASSERT_EQ(TIGL_SUCCESS, tiglCloseCPACSConfiguration(tiglHandle));
        ASSERT_EQ(SUCCESS, tixiCloseDocument(tixiHandle));
        tiglHandle = -1;
        tixiHandle = -1;
    }

    TixiDocumentHandle           tixiHandle;
    TiglCPACSConfigurationHandle tiglHandle;
};


TixiDocumentHandle WingComponentSegment::tixiHandle = 0;
TiglCPACSConfigurationHandle WingComponentSegment::tiglHandle = 0;

/******************************************************************************/


class WingComponentSegmentSimple : public ::testing::Test
{
protected:
    void SetUp() override
    {
        const char* filename = "TestData/simpletest.cpacs.xml";
        ReturnCode tixiRet;
        TiglReturnCode tiglRet;

        tiglHandle = -1;
        tixiHandle = -1;
        
        tixiRet = tixiOpenDocument(filename, &tixiHandle);
        ASSERT_TRUE (tixiRet == SUCCESS);

        tiglRet = tiglOpenCPACSConfiguration(tixiHandle, "Cpacs2Test", &tiglHandle);
        ASSERT_TRUE(tiglRet == TIGL_SUCCESS);
    }

    void TearDown() override
    {
        ASSERT_TRUE(tiglCloseCPACSConfiguration(tiglHandle) == TIGL_SUCCESS);
        ASSERT_TRUE(tixiCloseDocument(tixiHandle) == SUCCESS);
        tiglHandle = -1;
        tixiHandle = -1;
    }

    TixiDocumentHandle           tixiHandle;
    TiglCPACSConfigurationHandle tiglHandle;
};

TEST_F(WingComponentSegment, tiglWingGetComponentSegmentCount_success)
{
    int numCompSeg = 0;
    ASSERT_TRUE(tiglWingGetComponentSegmentCount(tiglHandle, 1, &numCompSeg) == TIGL_SUCCESS);
    ASSERT_TRUE(numCompSeg == 1);
}

TEST_F(WingComponentSegment, tiglWingGetComponentSegmentCount_wrongWing)
{
    int numCompSeg = 0;
    // this example contains only 3 wings
    ASSERT_TRUE(tiglWingGetComponentSegmentCount(tiglHandle, 4, &numCompSeg) == TIGL_INDEX_ERROR);
}

TEST_F(WingComponentSegment, tiglWingGetComponentSegmentCount_nullPtr)
{
    // this example contains only 3 wings
    ASSERT_TRUE(tiglWingGetComponentSegmentCount(tiglHandle, 1, NULL) == TIGL_NULL_POINTER);
}

TEST_F(WingComponentSegment, tiglWingGetComponentSegmentCount_wrongHandle)
{
    int numCompSeg = 0;
    TiglCPACSConfigurationHandle myWrongHandle = -1234;
    ASSERT_TRUE(tiglWingGetComponentSegmentCount(myWrongHandle, 1, &numCompSeg) == TIGL_NOT_FOUND);
}

TEST_F(WingComponentSegment, tiglWingGetComponentSegmentUID_success)
{
    char * uid = NULL;
    ASSERT_TRUE(tiglWingGetComponentSegmentUID(tiglHandle, 1, 1, &uid) == TIGL_SUCCESS);
    ASSERT_STREQ("D150_VAMP_W1_CompSeg1", uid);

    ASSERT_TRUE(tiglWingGetComponentSegmentUID(tiglHandle, 2, 1, &uid) == TIGL_SUCCESS);
    ASSERT_STREQ("D150_VAMP_HL1_CompSeg1", uid);

    ASSERT_TRUE(tiglWingGetComponentSegmentUID(tiglHandle, 3, 1, &uid) == TIGL_SUCCESS);
    ASSERT_STREQ("D150_VAMP_SL1_CompSeg1", uid);
}

TEST_F(WingComponentSegment, tiglWingGetComponentSegmentUID_indexFail)
{
    char * uid = NULL;
    ASSERT_TRUE(tiglWingGetComponentSegmentUID(tiglHandle, 1, 2, &uid) == TIGL_INDEX_ERROR);
    ASSERT_TRUE(tiglWingGetComponentSegmentUID(tiglHandle,-1, 1, &uid) == TIGL_INDEX_ERROR);
    ASSERT_TRUE(tiglWingGetComponentSegmentUID(tiglHandle, 4, 1, &uid) == TIGL_INDEX_ERROR);
}

TEST_F(WingComponentSegment, tiglWingComponentSegmentIndex_success)
{
    int segment = 0;
    ASSERT_TRUE(tiglWingGetComponentSegmentIndex(tiglHandle, 1, "D150_VAMP_W1_CompSeg1", &segment) == TIGL_SUCCESS);
    ASSERT_TRUE(segment == 1);

    segment = 0;
    ASSERT_TRUE(tiglWingGetComponentSegmentIndex(tiglHandle, 2, "D150_VAMP_HL1_CompSeg1", &segment) == TIGL_SUCCESS);
    ASSERT_TRUE(segment == 1);

    segment = 0;
    ASSERT_TRUE(tiglWingGetComponentSegmentIndex(tiglHandle, 3, "D150_VAMP_SL1_CompSeg1", &segment) == TIGL_SUCCESS);
    ASSERT_TRUE(segment == 1);
}

TEST_F(WingComponentSegment, tiglWingComponentSegmentIndex_wrongUID)
{
    int segment = 0;
    // component segment UID exist, but on wing 1
    ASSERT_TRUE(tiglWingGetComponentSegmentIndex(tiglHandle, 2, "D150_VAMP_W1_CompSeg1", &segment) == TIGL_UID_ERROR);

    ASSERT_TRUE(tiglWingGetComponentSegmentIndex(tiglHandle, 1, "invalid_uid", &segment) == TIGL_UID_ERROR);
}


TEST_F(WingComponentSegment, tiglWingComponentGetEtaXsi_success)
{
    double eta = 0.1103;
    double xsi = 0.812922;
    char * wingUID = NULL;
    char * segmentUID = NULL;
    double segmentEta = 0., segmentXsi = 0.;

    TiglReturnCode ret = tiglWingComponentSegmentPointGetSegmentEtaXsi(tiglHandle, "D150_VAMP_W1_CompSeg1", eta, xsi, &wingUID, &segmentUID, &segmentEta, &segmentXsi);
    ASSERT_TRUE( ret == TIGL_SUCCESS);
    ASSERT_STREQ("D150_VAMP_W1", wingUID);

    // test for a bug  in tigl 2.0.2, occurs when component segment does not lie on first wing
    eta = 0.16;
    xsi = 0.577506;
    ret = tiglWingComponentSegmentPointGetSegmentEtaXsi(tiglHandle, "D150_VAMP_HL1_CompSeg1", eta, xsi, &wingUID, &segmentUID, &segmentEta, &segmentXsi);
    ASSERT_TRUE(ret == TIGL_SUCCESS);
    ASSERT_STREQ("D150_VAMP_HL1", wingUID);
}

TEST_F(WingComponentSegment, tiglWingComponentGetEtaXsi_wrongUID)
{
    double eta = 0.1103;
    double xsi = 0.812922;
    char * wingUID = NULL;
    char * segmentUID = NULL;
    double segmentEta = 0., segmentXsi = 0.;

    TiglReturnCode ret = tiglWingComponentSegmentPointGetSegmentEtaXsi(tiglHandle, "invalid_comp_seg", eta, xsi, &wingUID, &segmentUID, &segmentEta, &segmentXsi);
    ASSERT_TRUE(ret == TIGL_UID_ERROR);
}


TEST_F(WingComponentSegment2, tiglWingComponentGetEtaXsi_success)
{
    double eta = 0.3336;
    double xsi = 0.;
    char * wingUID = NULL;
    char * segmentUID = NULL;
    double segmentEta = 0., segmentXsi = 0.;

    TiglReturnCode ret = tiglWingComponentSegmentPointGetSegmentEtaXsi(tiglHandle, "D250_wing_CS", eta, xsi, &wingUID, &segmentUID, &segmentEta, &segmentXsi);
    ASSERT_EQ(TIGL_SUCCESS, ret);
    ASSERT_STREQ("D250_wing", wingUID);

    eta = 0.;
    xsi = 0.5;

    ret = tiglWingComponentSegmentPointGetSegmentEtaXsi(tiglHandle, "D250_wing_CS", eta, xsi, &wingUID, &segmentUID, &segmentEta, &segmentXsi);
    ASSERT_EQ(TIGL_SUCCESS, ret);
    ASSERT_STREQ("D250_wing", wingUID);
}


TEST_F(WingComponentSegmentSimple, getPointInternal_accuracy)
{
    int compseg = 1;
    // now we have do use the internal interface as we currently have no public api for this
    tigl::CCPACSConfigurationManager & manager = tigl::CCPACSConfigurationManager::GetInstance();
    tigl::CCPACSConfiguration & config = manager.GetConfiguration(tiglHandle);
    tigl::CCPACSWing& wing = config.GetWing(1);
    tigl::CCPACSWingComponentSegment& segment = (tigl::CCPACSWingComponentSegment&) wing.GetComponentSegment(compseg);

    double eta = 0.5/(1 + sqrt(17./16.));
    gp_Pnt point = segment.GetPoint(eta, 0.5);
    ASSERT_NEAR(point.X(), 0.5, 1e-7);
    ASSERT_NEAR(point.Y(), 0.5, 1e-7);

    eta *= 2.;
    point = segment.GetPoint(eta, 0.5);
    ASSERT_NEAR(point.X(), 0.5, 1e-7);
    ASSERT_NEAR(point.Y(), 1.0, 1e-7);

    point = segment.GetPoint(1.0, 0.5);
    ASSERT_NEAR(point.X(), 0.75, 1e-7);
    ASSERT_NEAR(point.Y(), 2.0, 1e-7);

    eta += 0.5*(sqrt(17./16.))/(1. + (sqrt(17./16.)));
    point = segment.GetPoint(eta, 0.5);

    ASSERT_NEAR(point.X(), 0.625, 1e-7);
    ASSERT_NEAR(point.Y(), 1.5, 1e-7);
}


TEST_F(WingComponentSegmentSimple, getEtaXsi)
{
    int compseg = 1;
    // now we have do use the internal interface as we currently have no public api for this
    tigl::CCPACSConfigurationManager & manager = tigl::CCPACSConfigurationManager::GetInstance();
    tigl::CCPACSConfiguration & config = manager.GetConfiguration(tiglHandle);
    tigl::CCPACSWing& wing = config.GetWing(1);
    tigl::CCPACSWingComponentSegment& segment = (tigl::CCPACSWingComponentSegment&) wing.GetComponentSegment(compseg);

    double eta, xsi;
    gp_Pnt point = gp_Pnt(0.5, 0.5, 0.);
    segment.GetEtaXsi(point, eta, xsi);
    EXPECT_NEAR(0.5/(1 + sqrt(17./16.)), eta, 1e-6);
    EXPECT_NEAR(0.5, xsi, 1e-6);

    point = gp_Pnt(0.5, 1.0, 0.);
    segment.GetEtaXsi(point, eta, xsi);
    EXPECT_NEAR(1.0/(1 + sqrt(17./16.)), eta, 1e-6);
    EXPECT_NEAR(0.5, xsi, 1e-6);

    point = gp_Pnt(0.75, 2.0, 0.);
    segment.GetEtaXsi(point, eta, xsi);
    EXPECT_NEAR(1.0, eta, 1e-6);
    EXPECT_NEAR(0.5, xsi, 1e-6);

    point = gp_Pnt(0.625, 1.5, 0.);
    segment.GetEtaXsi(point, eta, xsi);
    EXPECT_NEAR((1. + 0.5*sqrt(17./16.))/(1. + sqrt(17./16.)), eta, 1e-6);
    EXPECT_NEAR(0.5, xsi, 1e-6);
}

TEST_F(WingComponentSegmentSimple, CCPACSWingComponentSegments)
{
    int compseg = 1;
    // now we have do use the internal interface as we currently have no public api for this
    tigl::CCPACSConfigurationManager & manager = tigl::CCPACSConfigurationManager::GetInstance();
    tigl::CCPACSConfiguration & config = manager.GetConfiguration(tiglHandle);
    const tigl::CTiglUIDManager& uidMgr = config.GetUIDManager();

    tigl::CCPACSWing& wing = config.GetWing(1);
    const tigl::CCPACSWingComponentSegment & segment = uidMgr.ResolveObject<tigl::CCPACSWingComponentSegment>("WING_CS1");
    const auto& psegments = segment.GetParent();

    EXPECT_EQ(&segment, &(psegments->GetComponentSegment(compseg)));
    EXPECT_EQ(&segment, &(psegments->GetComponentSegment("WING_CS1")));
    EXPECT_EQ(&segment, &(wing.GetComponentSegment("WING_CS1")));

    EXPECT_EQ(1, psegments->GetComponentSegmentCount());
    EXPECT_THROW(psegments->GetComponentSegment(2);, tigl::CTiglError);
}

TEST_F(WingComponentSegmentSimple, tiglWingComponentSegmentPointGetEtaXsi)
{
    double eta = 0., xsi = 0., errorDistance = 0.;

    ASSERT_EQ(TIGL_SUCCESS, tiglWingComponentSegmentPointGetEtaXsi(tiglHandle, "WING_CS1", 0.5, 0.5, 0., &eta, &xsi, &errorDistance));

    EXPECT_NEAR(0.5/(1 + sqrt(17./16.)), eta, 1e-6);
    EXPECT_NEAR(0.5, xsi, 1e-6);
    EXPECT_NEAR(0.0, errorDistance, 1e-6);

    ASSERT_EQ(TIGL_SUCCESS, tiglWingComponentSegmentPointGetEtaXsi(tiglHandle, "WING_CS1", 0.5, 1.0, 0., &eta, &xsi, &errorDistance));
    EXPECT_NEAR(1.0/(1 + sqrt(17./16.)), eta, 1e-6);
    EXPECT_NEAR(0.5, xsi, 1e-6);
    EXPECT_NEAR(0.0, errorDistance, 1e-6);

    ASSERT_EQ(TIGL_SUCCESS, tiglWingComponentSegmentPointGetEtaXsi(tiglHandle, "WING_CS1", 0.75, 2.0, 0., &eta, &xsi, &errorDistance));
    EXPECT_NEAR(1.0, eta, 1e-6);
    EXPECT_NEAR(0.5, xsi, 1e-6);
    EXPECT_NEAR(0.0, errorDistance, 1e-6);

    ASSERT_EQ(TIGL_SUCCESS, tiglWingComponentSegmentPointGetEtaXsi(tiglHandle, "WING_CS1", 0.625, 1.5, 0.2, &eta, &xsi, &errorDistance));
    EXPECT_NEAR((1. + 0.5*sqrt(17./16.))/(1. + sqrt(17./16.)), eta, 1e-6);
    EXPECT_NEAR(0.5, xsi, 1e-6);
    EXPECT_NEAR(0.2, errorDistance, 1e-6);

    // test api errors
    ASSERT_EQ(TIGL_UID_ERROR, tiglWingComponentSegmentPointGetEtaXsi(tiglHandle, "WING_CS1_INVALID", 0.5, 0.5, 0., &eta, &xsi, &errorDistance));
    ASSERT_EQ(TIGL_NULL_POINTER, tiglWingComponentSegmentPointGetEtaXsi(tiglHandle, NULL, 0.5, 0.5, 0., &eta, &xsi, &errorDistance));
    ASSERT_EQ(TIGL_NULL_POINTER, tiglWingComponentSegmentPointGetEtaXsi(tiglHandle, "WING_CS1", 0.5, 0.5, 0., NULL, &xsi, &errorDistance));
    ASSERT_EQ(TIGL_NULL_POINTER, tiglWingComponentSegmentPointGetEtaXsi(tiglHandle, "WING_CS1", 0.5, 0.5, 0., &eta, NULL, &errorDistance));
    ASSERT_EQ(TIGL_NULL_POINTER, tiglWingComponentSegmentPointGetEtaXsi(tiglHandle, "WING_CS1", 0.5, 0.5, 0., &eta, &xsi, NULL));
    ASSERT_EQ(TIGL_NOT_FOUND, tiglWingComponentSegmentPointGetEtaXsi(-1, "WING_CS1", 0.5, 0.5, 0., &eta, &xsi, &errorDistance));
}

TEST_F(WingComponentSegmentSimple, tiglWingComponentSegmentPointGetSegmentEtaXsi)
{
    // now the tests
    double csEta = 0., csXsi = 0.;
    char *wingUID = NULL, *segmentUID = NULL;

    ASSERT_EQ(TIGL_SUCCESS,
        tiglWingComponentSegmentPointGetSegmentEtaXsi(tiglHandle, "WING_CS1", 0.5 / (1. + sqrt(17./16.)), 0.5, &wingUID, &segmentUID, &csEta, &csXsi)
    );
    ASSERT_STREQ("Wing",wingUID);
    ASSERT_STREQ("Cpacs2Test_Wing_Seg_1_2", segmentUID);
    ASSERT_NEAR(csEta, 0.5, 1e-7);
    ASSERT_NEAR(csXsi, 0.5, 1e-7);

    ASSERT_EQ(TIGL_SUCCESS,
        tiglWingComponentSegmentPointGetSegmentEtaXsi(tiglHandle, "WING_CS1", 1.0 / (1. + sqrt(17./16.)) - 1e-11, 0.5, &wingUID, &segmentUID, &csEta, &csXsi)
    );
    ASSERT_STREQ("Wing",wingUID);
    ASSERT_STREQ("Cpacs2Test_Wing_Seg_1_2", segmentUID);
    ASSERT_NEAR(csEta, 1.0, 1e-7);
    ASSERT_NEAR(csXsi, 0.5, 1e-7);

    ASSERT_EQ(TIGL_SUCCESS,
        tiglWingComponentSegmentPointGetSegmentEtaXsi(tiglHandle, "WING_CS1", (1. + 0.5 * sqrt(17./16.)) / (1. + sqrt(17./16.)), 0.5, &wingUID, &segmentUID, &csEta, &csXsi)
    );
    ASSERT_STREQ("Wing",wingUID);
    ASSERT_STREQ("Cpacs2Test_Wing_Seg_2_3", segmentUID);
    ASSERT_NEAR(csEta, 0.5, 1e-7);
    ASSERT_NEAR(csXsi, 0.5, 1e-7);

    ASSERT_EQ(TIGL_UID_ERROR,
        tiglWingComponentSegmentPointGetSegmentEtaXsi(tiglHandle, "WRONG_UID", (1. + 0.5 * sqrt(17./16.)) / (1. + sqrt(17./16.)), 0.5, &wingUID, &segmentUID, &csEta, &csXsi)
    );

    ASSERT_EQ(TIGL_ERROR,
        tiglWingComponentSegmentPointGetSegmentEtaXsi(tiglHandle, "WING_CS1", -0.1, 0.5, &wingUID, &segmentUID, &csEta, &csXsi)
    );


}

TEST_F(WingComponentSegmentSimple, tiglWingComponentSegmentGetPoint_success)
{
    double accuracy = 1e-7;
    double x, y, z;
    ASSERT_EQ(TIGL_SUCCESS, tiglWingComponentSegmentGetPoint(tiglHandle, "WING_CS1", 1./ (1. + sqrt(17./16.)), 0.0, &x, &y, &z));
    ASSERT_NEAR(0.0, x, accuracy);
    ASSERT_NEAR(1.0, y, accuracy);
    ASSERT_NEAR(0.0, z, accuracy);
    
    ASSERT_EQ(TIGL_SUCCESS, tiglWingComponentSegmentGetPoint(tiglHandle, "WING_CS1", (1. + 0.5*sqrt(17./16.))/(1. + sqrt(17./16.)), 0.0, &x, &y, &z));
    ASSERT_NEAR(0.25, x, accuracy);
    ASSERT_NEAR(1.5, y, accuracy);
    ASSERT_NEAR(0.0, z, accuracy);
    
    ASSERT_EQ(TIGL_SUCCESS, tiglWingComponentSegmentGetPoint(tiglHandle, "WING_CS1", 1.0, 0.0, &x, &y, &z));
    ASSERT_NEAR(0.5, x, accuracy);
    ASSERT_NEAR(2.0, y, accuracy);
    ASSERT_NEAR(0.0, z, accuracy);
}

TEST_F(WingComponentSegmentSimple, GetSegmentEtaXsi)
{
    int compseg = 1;
    // now we have do use the internal interface as we currently have no public api for this
    tigl::CCPACSConfigurationManager & manager = tigl::CCPACSConfigurationManager::GetInstance();
    tigl::CCPACSConfiguration & config = manager.GetConfiguration(tiglHandle);
    tigl::CCPACSWing& wing = config.GetWing(1);
    tigl::CCPACSWingComponentSegment& csegment = (tigl::CCPACSWingComponentSegment&) wing.GetComponentSegment(compseg);

    std::string segmentUID;
    double sEta= -1., sXsi= -1.;
    ASSERT_NO_THROW(csegment.GetSegmentEtaXsi(0., 0., segmentUID, sEta, sXsi));

    EXPECT_NEAR(0., sEta, 1e-10);
    EXPECT_NEAR(0., sXsi, 1e-10);
    EXPECT_STREQ("Cpacs2Test_Wing_Seg_1_2", segmentUID.c_str());


    ASSERT_NO_THROW(csegment.GetSegmentEtaXsi(1./ (1. + sqrt(17./16.)), 0., segmentUID, sEta, sXsi));

    EXPECT_NEAR(0., sEta, 1e-10);
    EXPECT_NEAR(0., sXsi, 1e-10);
    EXPECT_STREQ("Cpacs2Test_Wing_Seg_2_3", segmentUID.c_str());

    ASSERT_NO_THROW(csegment.GetSegmentEtaXsi(1., 0.5, segmentUID, sEta, sXsi));

    EXPECT_NEAR(1., sEta, 1e-10);
    EXPECT_NEAR(0.5, sXsi, 1e-10);
    EXPECT_STREQ("Cpacs2Test_Wing_Seg_2_3", segmentUID.c_str());

    ASSERT_NO_THROW(csegment.GetSegmentEtaXsi((1. + 0.5*sqrt(17./16.)) / (1. + sqrt(17./16.)), 1.0, segmentUID, sEta, sXsi));

    EXPECT_NEAR(0.5, sEta, 1e-10);
    EXPECT_NEAR(1.0, sXsi, 1e-10);
    EXPECT_STREQ("Cpacs2Test_Wing_Seg_2_3", segmentUID.c_str());

    ASSERT_THROW(csegment.GetSegmentEtaXsi(-0.1, 1.0, segmentUID, sEta, sXsi), tigl::CTiglError);
    ASSERT_THROW(csegment.GetSegmentEtaXsi( 1.1, 1.0, segmentUID, sEta, sXsi), tigl::CTiglError);
    ASSERT_THROW(csegment.GetSegmentEtaXsi(0.5, -0.1, segmentUID, sEta, sXsi), tigl::CTiglError);
    ASSERT_THROW(csegment.GetSegmentEtaXsi(0.5,  1.1, segmentUID, sEta, sXsi), tigl::CTiglError);
}

TEST_F(WingComponentSegmentSimple, GetMaterials)
{
    int compseg = 1;
    // now we have do use the internal interface as we currently have no public api for this
    tigl::CCPACSConfigurationManager & manager = tigl::CCPACSConfigurationManager::GetInstance();
    tigl::CCPACSConfiguration & config = manager.GetConfiguration(tiglHandle);
    tigl::CCPACSWing& wing = config.GetWing(1);
    tigl::CCPACSWingComponentSegment& segment = (tigl::CCPACSWingComponentSegment&) wing.GetComponentSegment(compseg);
    
    // test point in cell
    tigl::MaterialList list = segment.GetMaterials(0.25, 0.9, UPPER_SHELL);
    ASSERT_EQ(1, list.size());
    ASSERT_STREQ("MyCellMat", list[0]->GetUID().c_str());
    
    // test point outside cell
    list = segment.GetMaterials(0.6, 0.9, UPPER_SHELL);
    ASSERT_EQ(1, list.size());
    ASSERT_STREQ("MySkinMat", list[0]->GetUID().c_str());
    
    // one material defined for lower shell
    list = segment.GetMaterials(0.6, 0.9, LOWER_SHELL);
    ASSERT_EQ(1, list.size());
}

TEST_F(WingComponentSegmentSimple, GetMaterials_cinterface)
{
    char *  uid = NULL;
    int matcount = 0;
    double thickness = -1;

    ASSERT_EQ(TIGL_SUCCESS, tiglWingComponentSegmentGetMaterialCount(tiglHandle, "WING_CS1", UPPER_SHELL, 0.25, 0.9, &matcount));
    ASSERT_EQ(1, matcount);

    ASSERT_EQ(TIGL_SUCCESS, tiglWingComponentSegmentGetMaterialUID(tiglHandle, "WING_CS1", UPPER_SHELL, 0.25, 0.9, 1, &uid));
    ASSERT_STREQ("MyCellMat", uid);

    ASSERT_EQ(TIGL_SUCCESS, tiglWingComponentSegmentGetMaterialThickness(tiglHandle, "WING_CS1", UPPER_SHELL, 0.25, 0.9, 1, &thickness));
    ASSERT_NEAR(0.0, thickness, 1e-10);
}

TEST_F(WingComponentSegmentSimple, GetMaterials_cinterface_nullptr)
{
    int ncount = 0;
    char * uid = NULL;
    ASSERT_EQ(TIGL_NULL_POINTER, tiglWingComponentSegmentGetMaterialUID(tiglHandle, NULL, UPPER_SHELL, 0.25, 0.9, 1, &uid));


    ASSERT_EQ(TIGL_NULL_POINTER, tiglWingComponentSegmentGetMaterialCount(tiglHandle, "WING_CS1", UPPER_SHELL, 0.25, 0.9, NULL));
    ASSERT_EQ(TIGL_NULL_POINTER, tiglWingComponentSegmentGetMaterialCount(tiglHandle, NULL, UPPER_SHELL, 0.25, 0.9, &ncount));
}

TEST_F(WingComponentSegmentSimple, determine_segments)
{
    int compseg = 1;
    // now we have do use the internal interface as we currently have no public api for this
    const tigl::CCPACSConfigurationManager & manager = tigl::CCPACSConfigurationManager::GetInstance();
    const tigl::CCPACSConfiguration & config = manager.GetConfiguration(tiglHandle);
    const tigl::CCPACSWing& wing = config.GetWing(1);
    const tigl::CCPACSWingComponentSegment& segment = wing.GetComponentSegment(compseg);

    const tigl::SegmentList& list = segment.GetSegmentList();
    ASSERT_EQ(2, list.size());
    ASSERT_STREQ("Cpacs2Test_Wing_Seg_1_2", list.at(0)->GetUID().c_str());
    ASSERT_STREQ("Cpacs2Test_Wing_Seg_2_3", list.at(1)->GetUID().c_str());
}

TEST_F(WingComponentSegmentSimple, GetSegments)
{
    int nsegments = 0;
    ASSERT_EQ(TIGL_SUCCESS, tiglWingComponentSegmentGetNumberOfSegments(tiglHandle, "WING_CS1", &nsegments));
    ASSERT_EQ(2, nsegments);
    
    char * seguid = NULL;
    ASSERT_EQ(TIGL_SUCCESS, tiglWingComponentSegmentGetSegmentUID(tiglHandle, "WING_CS1", 1, &seguid));
    ASSERT_STREQ("Cpacs2Test_Wing_Seg_1_2", seguid);
    
    ASSERT_EQ(TIGL_SUCCESS, tiglWingComponentSegmentGetSegmentUID(tiglHandle, "WING_CS1", 2, &seguid));
    ASSERT_STREQ("Cpacs2Test_Wing_Seg_2_3", seguid);
    
    // invalid cs uid
    ASSERT_EQ(TIGL_UID_ERROR, tiglWingComponentSegmentGetNumberOfSegments(tiglHandle, "INVALID_CS", &nsegments));
    ASSERT_EQ(TIGL_UID_ERROR, tiglWingComponentSegmentGetSegmentUID(tiglHandle, "INVALID_CS", 2, &seguid));
    
    // invalid segment index
    ASSERT_EQ(TIGL_INDEX_ERROR, tiglWingComponentSegmentGetSegmentUID(tiglHandle, "WING_CS1", 0, &seguid));
    ASSERT_EQ(TIGL_INDEX_ERROR, tiglWingComponentSegmentGetSegmentUID(tiglHandle, "WING_CS1", 3, &seguid));
    
    // nullptr
    ASSERT_EQ(TIGL_NULL_POINTER, tiglWingComponentSegmentGetNumberOfSegments(tiglHandle, NULL, &nsegments));
    ASSERT_EQ(TIGL_NULL_POINTER, tiglWingComponentSegmentGetNumberOfSegments(tiglHandle, "WING_CS1", NULL));
    ASSERT_EQ(TIGL_NULL_POINTER, tiglWingComponentSegmentGetSegmentUID(tiglHandle, NULL, 1, &seguid));
    ASSERT_EQ(TIGL_NULL_POINTER, tiglWingComponentSegmentGetSegmentUID(tiglHandle, "WING_CS1", 1, NULL));
    
    // invalid handle
    ASSERT_EQ(TIGL_NOT_FOUND, tiglWingComponentSegmentGetNumberOfSegments(-1, "WING_CS1", &nsegments));
    ASSERT_EQ(TIGL_NOT_FOUND, tiglWingComponentSegmentGetSegmentUID(-1, "WING_CS1", 1, &seguid));
}

TEST_F(WingComponentSegmentSimple, GetEtaXsiFromSegment)
{
    int compseg = 1;
    // now we have do use the internal interface as we currently have no public api for this
    tigl::CCPACSConfigurationManager & manager = tigl::CCPACSConfigurationManager::GetInstance();
    tigl::CCPACSConfiguration & config = manager.GetConfiguration(tiglHandle);
    tigl::CCPACSWing& wing = config.GetWing(1);
    tigl::CCPACSWingComponentSegment& segment = (tigl::CCPACSWingComponentSegment&) wing.GetComponentSegment(compseg);
    
    double eta, xsi;
    segment.GetEtaXsiFromSegmentEtaXsi("Cpacs2Test_Wing_Seg_1_2", 0.5, 0.5, eta, xsi);
    ASSERT_NEAR(0.5/ (1. + sqrt(17./16.)), eta, 1e-7);
    ASSERT_NEAR(0.50, xsi, 1e-7);
}

TEST_F(WingComponentSegmentSimple, tiglWingSegmentPointGetComponentSegmentEtaXsi_success)
{
    double eta, xsi;
    ASSERT_EQ(TIGL_SUCCESS, tiglWingSegmentPointGetComponentSegmentEtaXsi(tiglHandle, "Cpacs2Test_Wing_Seg_1_2", "WING_CS1", 0.5, 0.5, &eta, &xsi));
    ASSERT_NEAR(0.5 / (1. + sqrt(17./16.)), eta, 1e-7);
    ASSERT_NEAR(0.50, xsi, 1e-7);
    
    ASSERT_EQ(TIGL_SUCCESS, tiglWingSegmentPointGetComponentSegmentEtaXsi(tiglHandle, "Cpacs2Test_Wing_Seg_2_3", "WING_CS1", 0.5, 0.5, &eta, &xsi));
    ASSERT_NEAR((1 + 0.5*sqrt(17./16.))/(1. + sqrt(17./16.)), eta, 1e-7);
    ASSERT_NEAR(0.50, xsi, 1e-7);
}

TEST_F(WingComponentSegmentSimple, GetSegmentIntersection_cinterface)
{
    double xsi;
    TiglReturnCode ret;
    TiglBoolean hasWarning;
    ret = tiglWingComponentSegmentGetSegmentIntersection(tiglHandle, "WING_CS1", "Cpacs2Test_Wing_Seg_1_2", 0.0, 0.0, 1.0, 1.0, 1.0, &xsi, &hasWarning);
    ASSERT_EQ(TIGL_SUCCESS, ret);
    ASSERT_NEAR(0.5, xsi, 1e-6);

    ret = tiglWingComponentSegmentGetSegmentIntersection(tiglHandle, "WING_CS1","Cpacs2Test_Wing_Seg_2_3", 0.1, 0.1, 0.9, 0.1, 1.0, &xsi, &hasWarning);
    ASSERT_EQ(TIGL_MATH_ERROR, ret);

    ret = tiglWingComponentSegmentGetSegmentIntersection(tiglHandle, "","Cpacs2Test_Wing_Seg_1_2", 0.1, 0.1, 0.9, 0.1, 1.0, &xsi, &hasWarning);
    ASSERT_EQ(TIGL_UID_ERROR, ret);

    ret = tiglWingComponentSegmentGetSegmentIntersection(tiglHandle, "WING_CS1", "", 0.1, 0.1, 0.9, 0.1, 1.0, &xsi, &hasWarning);
    ASSERT_EQ(TIGL_UID_ERROR, ret);

    ret = tiglWingComponentSegmentGetSegmentIntersection(tiglHandle, NULL, "Cpacs2Test_Wing_Seg_1_2", 0.1, 0.1, 0.9, 0.1, 1.0, &xsi, &hasWarning);
    ASSERT_EQ(TIGL_NULL_POINTER, ret);

    ret = tiglWingComponentSegmentGetSegmentIntersection(tiglHandle, "WING_CS1", NULL, 0.1, 0.1, 0.9, 0.1, 1.0, &xsi, &hasWarning);
    ASSERT_EQ(TIGL_NULL_POINTER, ret);

    ret = tiglWingComponentSegmentGetSegmentIntersection(tiglHandle, "WING_CS1", "Cpacs2Test_Wing_Seg_1_2", 0.1, 0.1, 0.9, 0.1, 1.0, NULL, &hasWarning);
    ASSERT_EQ(TIGL_NULL_POINTER, ret);
}

TEST_F(WingComponentSegmentSimple, IntersectEta_cinterface)
{
    double xsi;
    TiglBoolean hasWarning;
    ASSERT_EQ(TIGL_SUCCESS, tiglWingComponentSegmentComputeEtaIntersection(tiglHandle, "WING_CS1", 0.0, 0.0, 1.0, 1.0, (1 + 0.8*sqrt(17./16.)) / (1. + sqrt(17./16.)), &xsi, &hasWarning));
    ASSERT_NEAR(0.5/0.6, xsi, 1e-6);
    ASSERT_EQ(TIGL_FALSE, hasWarning);
    ASSERT_EQ(TIGL_SUCCESS, tiglWingComponentSegmentComputeEtaIntersection(tiglHandle, "WING_CS1", 0.0, 0.0, 1.0, 1.0, 0.9, &xsi, NULL));

    // check invalid input
    ASSERT_EQ(TIGL_NULL_POINTER, tiglWingComponentSegmentComputeEtaIntersection(tiglHandle, "WING_CS1", 0.0, 0.0, 1.0, 1.0, 0.9, NULL, &hasWarning));

    ASSERT_EQ(TIGL_NULL_POINTER, tiglWingComponentSegmentComputeEtaIntersection(tiglHandle, NULL, 0.0, 0.0, 1.0, 1.0, 0.9, &xsi, &hasWarning));

    ASSERT_EQ(TIGL_UID_ERROR, tiglWingComponentSegmentComputeEtaIntersection(tiglHandle, "invalidcs", 0.0, 0.0, 1.0, 1.0, 0.9, &xsi, &hasWarning));

    ASSERT_EQ(TIGL_MATH_ERROR, tiglWingComponentSegmentComputeEtaIntersection(tiglHandle, "WING_CS1", 0.0, 0.0, 1.0, 1.0, 2.0, &xsi, &hasWarning));
}

/// Tests the math of the new component segment definition
TEST_F(WingComponentSegmentSimple, wingChordFace)
{
    const tigl::CCPACSConfigurationManager & manager = tigl::CCPACSConfigurationManager::GetInstance();
    const tigl::CCPACSConfiguration & config = manager.GetConfiguration(tiglHandle);
    const tigl::CCPACSWing& wing = config.GetWing(1);
    const tigl::CCPACSWingComponentSegment& compSegment = (tigl::CCPACSWingComponentSegment&) wing.GetComponentSegment(1);

    const tigl::CTiglWingChordface& chordFace = compSegment.GetChordface();

    std::vector<double> etas = chordFace.GetElementEtas();

    ASSERT_EQ(3, etas.size());
    EXPECT_NEAR(0., etas[0], 1e-10);
    EXPECT_NEAR(1./ (1. + sqrt(17./16.)), etas[1], 1e-10);
    EXPECT_NEAR(1., etas[2], 1e-10);

    EXPECT_NEAR(0., chordFace.GetPoint(0., 0.).Distance(gp_Pnt(0., 0., 0.)), 1e-10);
    EXPECT_NEAR(0., chordFace.GetPoint(0., 1.).Distance(gp_Pnt(1., 0., 0.)), 1e-10);
    EXPECT_NEAR(0., chordFace.GetPoint(etas[1], 0.).Distance(gp_Pnt(0., 1., 0.)), 1e-10);
    EXPECT_NEAR(0., chordFace.GetPoint(etas[1], 1.).Distance(gp_Pnt(1., 1., 0.)), 1e-10);
    EXPECT_NEAR(0., chordFace.GetPoint(etas[2], 0.).Distance(gp_Pnt(0.5, 2., 0.)), 1e-10);
    EXPECT_NEAR(0., chordFace.GetPoint(etas[2], 1.).Distance(gp_Pnt(1., 2., 0.)), 1e-10);
    EXPECT_NEAR(0., chordFace.GetPoint((etas[1] + etas[2])*0.5, 0.0).Distance(gp_Pnt(0.25, 1.5, 0.)), 1e-10);
    EXPECT_NEAR(0., chordFace.GetPoint((etas[1] + etas[2])*0.5, 0.5).Distance(gp_Pnt(0.75/2. + 0.25, 1.5, 0.)), 1e-10);
    EXPECT_NEAR(0., chordFace.GetPoint((etas[1] + etas[2])*0.5, 1.0).Distance(gp_Pnt(1.0, 1.5, 0.)), 1e-10);
}

TEST_F(WingComponentSegment3, tiglWingComponentSegmentPointGetSegmentEtaXsi_BUG1)
{
    // now the tests
    double sEta = 0., sXsi = 0.;
    char *wingUID = NULL, *segmentUID = NULL;

    TiglReturnCode ret = tiglWingComponentSegmentPointGetSegmentEtaXsi(tiglHandle, "D150_wing_CS", 0.0, 0.0, &wingUID, &segmentUID, &sEta, &sXsi);
    ASSERT_EQ(TIGL_SUCCESS, ret);
    ASSERT_STREQ("D150_wing_1ID", wingUID);
    ASSERT_STREQ("D150_wing_1Segment2ID", segmentUID);
}

TEST(WingComponentSegment4, tiglWingComponentSegmentPointGetSegmentEtaXsi_BUG2)
{
    TiglCPACSConfigurationHandle tiglHandle = -1;
    TixiDocumentHandle tixiHandle = -1;
    
    const char* filename = "TestData/simple_rectangle_compseg.xml";
    
    ReturnCode tixiRet = tixiOpenDocument(filename, &tixiHandle);
    ASSERT_TRUE (tixiRet == SUCCESS);
    TiglReturnCode tiglRet = tiglOpenCPACSConfiguration(tixiHandle, "D150modelID", &tiglHandle);
    ASSERT_TRUE(tiglRet == TIGL_SUCCESS);
    
    double sEta = 0., sXsi = 0.;
    char *wingUID = NULL, *segmentUID = NULL;

    tiglRet = tiglWingComponentSegmentPointGetSegmentEtaXsi(tiglHandle, "D150_wing_CS", 0.5, 0.10142, &wingUID, &segmentUID, &sEta, &sXsi);
    ASSERT_EQ(TIGL_SUCCESS, tiglRet);
    ASSERT_STREQ("D150_wing_1Segment3ID", segmentUID);
    ASSERT_NEAR(0.5, sEta, 0.0001);

    tiglCloseCPACSConfiguration(tiglHandle);
    tixiCloseDocument(tixiHandle);
}

TEST_F(WingComponentSegment3, tiglWingComponentSegmentPointGetSegmentEtaXsi_BUG3)
{
    double sEta = 0., sXsi = 0.;
    char *wingUID = NULL, *segmentUID = NULL;

    TiglReturnCode ret = tiglWingComponentSegmentPointGetSegmentEtaXsi(tiglHandle, "D150_VTP_CS", 0.0, 1.0, &wingUID, &segmentUID, &sEta, &sXsi);
    ASSERT_EQ(TIGL_SUCCESS, ret);
    ASSERT_STREQ("D150_VTP_1ID", wingUID);
    ASSERT_STREQ("D150_VTP_1Segment2ID", segmentUID);

    ASSERT_NEAR(0.0, sEta, 0.0001);
    ASSERT_NEAR(1.0, sXsi, 0.0001);
}

TEST_F(WingComponentSegment, tiglWingComponentSegmentPointGetSegmentEtaXsi_BUG4)
{
    double sEta = 0., sXsi = 0.;
    char *wingUID = NULL, *segmentUID = NULL;

    TiglReturnCode tiglRet = tiglWingComponentSegmentPointGetSegmentEtaXsi(tiglHandle, "D150_VAMP_SL1_CompSeg1", 0.95, 0.714, &wingUID, &segmentUID, &sEta, &sXsi);
    ASSERT_EQ(TIGL_SUCCESS, tiglRet);
}

TEST_F(WingComponentSegment, tiglWingComponentFindSegment_BUG)
{
    double px, py, pz;
    char *wingUID = NULL, *segmentUID = NULL;
    ASSERT_EQ(TIGL_SUCCESS, tiglWingGetUpperPoint(tiglHandle, 1, 1, 0.5, 0.5, &px, &py, &pz));
    TiglReturnCode tiglRet = tiglWingComponentSegmentFindSegment(tiglHandle, "D150_VAMP_W1_CompSeg1", px, py, pz, &segmentUID, &wingUID);
    ASSERT_EQ(TIGL_SUCCESS, tiglRet);
}

TEST(WingComponentSegment5, GetSegmentIntersection_BUG)
{
    const char* filename = "TestData/CS_SegIntersectionBUG.xml";
    ReturnCode tixiRet;
    TiglReturnCode tiglRet;

    TiglCPACSConfigurationHandle tiglHandle = -1;
    TixiDocumentHandle tixiHandle = -1;

    tixiRet = tixiOpenDocument(filename, &tixiHandle);
    ASSERT_EQ (SUCCESS, tixiRet);
    tiglRet = tiglOpenCPACSConfiguration(tixiHandle, "", &tiglHandle);
    ASSERT_EQ(TIGL_SUCCESS, tiglRet);

    double xsi = 0;
    TiglBoolean hasWarning;
    tiglRet = tiglWingComponentSegmentGetSegmentIntersection(tiglHandle, "wing_Cseg", "wing_Seg2", 0.0521575, 1., 0.328047, 1., 1., &xsi, &hasWarning);
    ASSERT_EQ(TIGL_SUCCESS, tiglRet);
    ASSERT_EQ(TIGL_TRUE, hasWarning);
    ASSERT_NEAR(1.0, xsi, 1e-2);

    ASSERT_EQ(TIGL_SUCCESS, tiglCloseCPACSConfiguration(tiglHandle));
    ASSERT_EQ(SUCCESS, tixiCloseDocument(tixiHandle));
}

/// A reported bug, where tigl creates an invalid error
TEST(WingComponentSegment5, GetSegmentIntersection_BUG2)
{
    const char* filename = "TestData/component-segment-bwb.xml";

    TiglCPACSConfigurationHandle tiglHandle = -1;
    TixiDocumentHandle tixiHandle = -1;

    ASSERT_EQ (SUCCESS, tixiOpenDocument(filename, &tixiHandle));
    ASSERT_EQ(TIGL_SUCCESS, tiglOpenCPACSConfiguration(tixiHandle, "", &tiglHandle));

    double xsi = 0;
    TiglBoolean hasWarning;
    ASSERT_EQ(TIGL_SUCCESS, tiglWingComponentSegmentGetSegmentIntersection(
               tiglHandle, "BWB_CST_wing_CS", "BWB_CST_wingSegment49ID", 
               0.81268, 1., 0.96, 1., 1., 
               &xsi, &hasWarning));

    ASSERT_EQ(TIGL_TRUE, hasWarning);
    ASSERT_EQ(TIGL_SUCCESS, tiglCloseCPACSConfiguration(tiglHandle));
    ASSERT_EQ(SUCCESS, tixiCloseDocument(tixiHandle));
}

/// A reported bug, where the specified points do only
/// almost intersect the section border. TiGL has to be
/// friendly enough to let this small deviation happen
TEST(WingComponentSegment5, GetSegmentIntersection_BUG3)
{
    const char* filename = "TestData/simpletest.cpacs.xml";

    TiglCPACSConfigurationHandle tiglHandle = -1;
    TixiDocumentHandle tixiHandle = -1;

    ASSERT_EQ (SUCCESS, tixiOpenDocument(filename, &tixiHandle));
    ASSERT_EQ(TIGL_SUCCESS, tiglOpenCPACSConfiguration(tixiHandle, "", &tiglHandle));

    double xsi = 0;
    // The segment border should be in tolerance
    ASSERT_EQ(TIGL_SUCCESS, tiglWingComponentSegmentGetSegmentIntersection(
               tiglHandle, "WING_CS1", "Cpacs2Test_Wing_Seg_1_2", 
               0.0, 0.7, 1. / (1. + sqrt(17./16.)) - 1e-6, 0.7, 1.,
               &xsi, NULL));

    ASSERT_NEAR(0.7, xsi, 1e-7);
    // This is too inaccurate now
    ASSERT_EQ(TIGL_MATH_ERROR, tiglWingComponentSegmentGetSegmentIntersection(
               tiglHandle, "WING_CS1", "Cpacs2Test_Wing_Seg_1_2", 
               0.0, 0.7, 1. / (1. + sqrt(17./16.)) - 1e-5, 0.7, 1.,
               &xsi, NULL));

    // check inner section
    // The segment border is at eta = 0.0. we test if 0.000005 is okay (all values below should fail)
    ASSERT_EQ(TIGL_SUCCESS, tiglWingComponentSegmentGetSegmentIntersection(
               tiglHandle, "WING_CS1", "Cpacs2Test_Wing_Seg_1_2", 
               (1e-5)/2. - 1e-6, 0.7, 0.5 + 1e-5, 0.7, 0., 
               &xsi, NULL));

    // This should be too inaccurate now
    ASSERT_EQ(TIGL_MATH_ERROR, tiglWingComponentSegmentGetSegmentIntersection(
               tiglHandle, "WING_CS1", "Cpacs2Test_Wing_Seg_1_2", 
               (1e-5)/2. + 1e-5, 0.7, 0.5 + 1e-5, 0.7, 0., 
               &xsi, NULL));

    ASSERT_EQ(TIGL_SUCCESS, tiglCloseCPACSConfiguration(tiglHandle));
    ASSERT_EQ(SUCCESS, tixiCloseDocument(tixiHandle));
}

/// This is a component segment with many segments
TEST(WingComponentSegment5, GetPointPerformance)
{
    const char* filename = "TestData/component-segment-bwb.xml";
    char* csUID = NULL;
    ReturnCode tixiRet;
    TiglReturnCode tiglRet;

    TiglCPACSConfigurationHandle tiglHandle = -1;
    TixiDocumentHandle tixiHandle = -1;

    tixiRet = tixiOpenDocument(filename, &tixiHandle);
    ASSERT_EQ (SUCCESS, tixiRet);
    tiglRet = tiglOpenCPACSConfiguration(tixiHandle, "", &tiglHandle);
    ASSERT_EQ(TIGL_SUCCESS, tiglRet);
    
    tiglWingGetComponentSegmentUID(tiglHandle, 1, 1, &csUID);

    int nruns = 50;
    double x, y, z;
    double w = 0.;
    
    // first run takes longer due to creation of leading edge. we dont count it
    tiglRet = tiglWingComponentSegmentGetPoint(tiglHandle, csUID, 0.95, 0.8, &x, &y, &z);
    
    clock_t start = clock();
    for(int i = 0; i < nruns; ++i){
        tiglRet = tiglWingComponentSegmentGetPoint(tiglHandle, csUID, 0.95, 0.8, &x, &y, &z);
        //just some dummy to prevent compiler optimization
        w = w + 1.0;
    }

    clock_t stop = clock();
    ASSERT_EQ((double)nruns, w);
        
    double time_elapsed = (double)(stop - start)/(double)CLOCKS_PER_SEC/(double)nruns;
    time_elapsed *= 1000.;
    printf("Average time: %f [ms]\n", time_elapsed);
    
    ASSERT_EQ(TIGL_SUCCESS, tiglCloseCPACSConfiguration(tiglHandle));
    ASSERT_EQ(SUCCESS, tixiCloseDocument(tixiHandle));
}

TEST(WingComponentSegment5, IntersectEta_bug)
{
    const char* filename = "TestData/compseg-rotated.xml";
    ReturnCode tixiRet;
    TiglReturnCode tiglRet;

    TiglCPACSConfigurationHandle tiglHandle = -1;
    TixiDocumentHandle tixiHandle = -1;

    tixiRet = tixiOpenDocument(filename, &tixiHandle);
    ASSERT_EQ (SUCCESS, tixiRet);
    tiglRet = tiglOpenCPACSConfiguration(tixiHandle, "", &tiglHandle);
    ASSERT_EQ(TIGL_SUCCESS, tiglRet);

    double xsi;
    TiglBoolean hasWarning;
    ASSERT_EQ(TIGL_SUCCESS, tiglWingComponentSegmentComputeEtaIntersection(tiglHandle, "D150_wing_CS", 0.0, 0.5, 1.0, 0.5, 0.9, &xsi, &hasWarning));
    ASSERT_NEAR(0.5, xsi, 1e-6);

    ASSERT_EQ(TIGL_SUCCESS, tiglWingComponentSegmentComputeEtaIntersection(tiglHandle, "D150_wing_CS", 0.0, 0.5, 1.0, 0.5, 0.1, &xsi, &hasWarning));
    ASSERT_NEAR(0.5, xsi, 1e-6);

    // Test some invalid inputs
    ASSERT_EQ(TIGL_MATH_ERROR, tiglWingComponentSegmentComputeEtaIntersection(tiglHandle, "D150_wing_CS", 0.0, 0.5, 1.0, 0.5, 1.1, &xsi, &hasWarning));
    ASSERT_EQ(TIGL_MATH_ERROR, tiglWingComponentSegmentComputeEtaIntersection(tiglHandle, "D150_wing_CS", 0.0, 0.5, 1.0, 0.5, -0.1, &xsi, &hasWarning));
    ASSERT_EQ(TIGL_ERROR, tiglWingComponentSegmentComputeEtaIntersection(tiglHandle, "D150_wing_CS", -0.1, 0.5, 1.0, 0.5, 0.7, &xsi, &hasWarning));
    ASSERT_EQ(TIGL_ERROR, tiglWingComponentSegmentComputeEtaIntersection(tiglHandle, "D150_wing_CS", 0.0, 0.5, 1.1, 0.5, 0.7, &xsi, &hasWarning));

    ASSERT_EQ(TIGL_SUCCESS, tiglCloseCPACSConfiguration(tiglHandle));
    ASSERT_EQ(SUCCESS, tixiCloseDocument(tixiHandle));
}
