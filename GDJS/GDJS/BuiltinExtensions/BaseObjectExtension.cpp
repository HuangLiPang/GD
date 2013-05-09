#include "BaseObjectExtension.h"
#include "GDCore/Events/EventsCodeGenerator.h"
#include "GDCore/CommonTools.h"
#include <wx/intl.h>
//Ensure the wxWidgets macro "_" returns a std::string
#if defined(_)
    #undef _
#endif
#define _(s) std::string(wxGetTranslation((s)).mb_str())

BaseObjectExtension::BaseObjectExtension()
{
    SetExtensionInformation("BuiltinObject",
                          _("Base object"),
                          _("Base object"),
                          "Compil Games",
                          "Freeware");
    CloneExtension("Game Develop C++ platform", "BuiltinObject");

    std::map<std::string, gd::InstructionMetadata > & objectActions = GetAllActionsForObject("");
    std::map<std::string, gd::InstructionMetadata > & objectConditions = GetAllConditionsForObject("");
    std::map<std::string, gd::ExpressionMetadata > & objectExpressions = GetAllExpressionsForObject("");
    std::map<std::string, gd::StrExpressionMetadata > & objectStrExpressions = GetAllStrExpressionsForObject("");

    objectActions["MettreX"].codeExtraInformation
        .SetFunctionName("setX").SetAssociatedGetter("getX").SetIncludeFile("runtimeobject.js");
    objectActions["MettreY"].codeExtraInformation
        .SetFunctionName("setY").SetAssociatedGetter("getY").SetIncludeFile("runtimeobject.js");
    objectConditions["PosX"].codeExtraInformation
        .SetFunctionName("getX").SetIncludeFile("runtimeobject.js");
    objectConditions["PosY"].codeExtraInformation
        .SetFunctionName("getY").SetIncludeFile("runtimeobject.js");
    /*objectConditions["MettreXY"].codeExtraInformation
        .SetFunctionName("changeXY").SetIncludeFile("runtimeobject.js");*/ //TODO
    objectActions["ChangeLayer"].codeExtraInformation
        .SetFunctionName("setLayer").SetIncludeFile("runtimeobject.js");
    objectConditions["Layer"].codeExtraInformation
        .SetFunctionName("isOnLayer").SetIncludeFile("runtimeobject.js");
    objectActions["ChangePlan"].codeExtraInformation
        .SetFunctionName("setZOrder").SetAssociatedGetter("getZOrder").SetIncludeFile("runtimeobject.js");
    objectConditions["Plan"].codeExtraInformation
        .SetFunctionName("getZOrder").SetIncludeFile("runtimeobject.js");
    objectActions["Cache"].codeExtraInformation
        .SetFunctionName("hide").SetIncludeFile("runtimeobject.js");
    objectActions["Montre"].codeExtraInformation
        .SetFunctionName("hide").SetIncludeFile("runtimeobject.js");
    objectConditions["Visible"].codeExtraInformation
        .SetFunctionName("isVisible").SetIncludeFile("runtimeobject.js");
    objectConditions["Invisible"].codeExtraInformation
        .SetFunctionName("isHidden").SetIncludeFile("runtimeobject.js");
    objectActions["Delete"].codeExtraInformation
        .SetFunctionName("deleteFromScene");
    objectActions["MettreAutourPos"].codeExtraInformation
        .SetFunctionName("putAround");
    objectConditions["VarObjet"].codeExtraInformation
        .SetFunctionName("getVariableValue").SetIncludeFile("runtimeobject.js");
    objectConditions["VarObjetTxt"].codeExtraInformation
        .SetFunctionName("getVariableValue").SetIncludeFile("runtimeobject.js");
    objectConditions["VarObjetDef"].codeExtraInformation
        .SetFunctionName("hasVariable").SetIncludeFile("runtimeobject.js");
    objectActions["ModVarObjet"].codeExtraInformation
        .SetFunctionName("setVariableValue").SetAssociatedGetter("getVariableValue").SetIncludeFile("runtimeobject.js");
    objectActions["ModVarObjetTxt"].codeExtraInformation
        .SetFunctionName("setVariableValue").SetAssociatedGetter("getVariableValue").SetIncludeFile("runtimeobject.js");

    objectExpressions["X"].codeExtraInformation.SetFunctionName("getX");
    objectExpressions["Y"].codeExtraInformation.SetFunctionName("getY");
    objectExpressions["ZOrder"].codeExtraInformation.SetFunctionName("getZOrder");
    objectExpressions["Plan"].codeExtraInformation.SetFunctionName("getZOrder");
    objectExpressions["Width"].codeExtraInformation.SetFunctionName("getWidth");
    objectExpressions["Height"].codeExtraInformation.SetFunctionName("getHeight");
    objectExpressions["Largeur"].codeExtraInformation.SetFunctionName("getWidth"); //Deprecated
    objectExpressions["Hauteur"].codeExtraInformation.SetFunctionName("getHeight"); //Deprecated
    objectExpressions["Variable"].codeExtraInformation.SetFunctionName("getVariableValue");
    objectStrExpressions["VariableString"].codeExtraInformation.SetFunctionName("getVariableValue");

    GetAllActions()["Create"].codeExtraInformation
        .SetFunctionName("gdjs.createObjectOnScene");
    GetAllActions()["CreateByName"].codeExtraInformation
        .SetFunctionName("gdjs.createObjectOnScene");
    GetAllExpressions()["Count"].codeExtraInformation
        .SetFunctionName("gdjs.pickedObjectsCount");
    GetAllConditions()["NbObjet"].codeExtraInformation
        .SetFunctionName("gdjs.pickedObjectsCount");

/*


        obj.AddAction("AddForceXY",
                       _("Add a force to an object"),
                       _("Add a force to an object. The object will move according to\nall forces it owns. This action create the force with its X and Y coordinates."),
                       _("Add to _PARAM0_ a force of _PARAM1_ p/s on X axis and _PARAM2_ p/s on Y axis"),
                       _("Displacement"),
                       "res/actions/force24.png",
                       "res/actions/force.png")

            .AddParameter("object", _("Object"))
            .AddParameter("expression", _("X coordinate of moving"))
            .AddParameter("expression", _("Y coordinate of moving"))
            .AddParameter("expression", _("Damping ( Default : 0 )"))
            .codeExtraInformation.SetFunctionName("AddForce");

        obj.AddAction("AddForceAL",
                       _("Add a force ( angle )"),
                       _("Add a force to an object. The object will move according to\nall forces it owns. This action creates the force using the specified angle and length."),
                       _("Add to _PARAM0_ a force, angle : _PARAM1_� and length : _PARAM2_ pixels"),
                       _("Displacement"),
                       "res/actions/force24.png",
                       "res/actions/force.png")

            .AddParameter("object", _("Object"))
            .AddParameter("expression", _("Angle"))
            .AddParameter("expression", _("Length ( in pixels )"))
            .AddParameter("expression", _("Damping ( Default : 0 )"))
            .codeExtraInformation.SetFunctionName("AddForceUsingPolarCoordinates");


        obj.AddAction("AddForceVersPos",
                       _("Add a force so as to move to a position"),
                       _("Add a force to an object so as it moves to the position."),
                       _("Move _PARAM0_ to _PARAM1_;_PARAM2_ with a force of _PARAM3_ pixels"),
                       _("Displacement"),
                       "res/actions/force24.png",
                       "res/actions/force.png")

            .AddParameter("object", _("Object"))
            .AddParameter("expression", _("X position"))
            .AddParameter("expression", _("Y position"))
            .AddParameter("expression", _("Length ( in pixels )"))
            .AddParameter("expression", _("Damping ( Default : 0 )"))
            .codeExtraInformation.SetFunctionName("AddForceTowardPosition");


        obj.AddAction("AddForceTournePos",
                       _("Add a force so as to move around a position"),
                       _("Add a force to an object so as it rotates toward a position.\nNote that the moving is not precise, especially if the speed is high.\nTo position an object around a position more precisly, use the actions in the category  \"Position\"."),
                       _("Rotate _PARAM0_ around _PARAM1_;_PARAM2_ with _PARAM3_�/sec and _PARAM4_ pixels away"),
                       _("Displacement"),
                       "res/actions/forceTourne24.png",
                       "res/actions/forceTourne.png")

            .AddParameter("object", _("Object"))
            .AddParameter("expression", _("X position of the center"))
            .AddParameter("expression", _("Y position of the center"))
            .AddParameter("expression", _("Speed ( in Degrees per seconds )"))
            .AddParameter("expression", _("Distance ( in pixels )"))
            .AddParameter("expression", _("Damping ( Default : 0 )"))
            .codeExtraInformation.SetFunctionName("AddForceToMoveAround");


        obj.AddAction("Arreter",
                       _("Stop the object"),
                       _("Stop the object by deleting all its forces."),
                       _("Stop the object _PARAM0_"),
                       _("Displacement"),
                       "res/actions/arreter24.png",
                       "res/actions/arreter.png")

            .AddParameter("object", _("Object"))
            .codeExtraInformation.SetFunctionName("ClearForce");

        obj.AddAction("Duplicate",
                       _("Duplicate an object"),
                       _("Create a copy of an object"),
                       _("Duplicate the object _PARAM0_"),
                       _("Objects"),
                       "res/actions/duplicate24.png",
                       "res/actions/duplicate.png")

            .AddParameter("object", _("Object"))
            .AddCodeOnlyParameter("currentScene", "")
            .AddCodeOnlyParameter("mapOfObjectListsOfParameter", "0")
            .codeExtraInformation.SetFunctionName("Duplicate");


        obj.AddCondition("Arret",
                       _("An object is stopped"),
                       _("Test if an object does not move"),
                       _("_PARAM0_ is stopped"),
                       _("Displacement"),
                       "res/conditions/arret24.png",
                       "res/conditions/arret.png")

            .AddParameter("object", _("Object"))
            .codeExtraInformation.SetFunctionName("IsStopped");

        obj.AddCondition("Vitesse",
                       _("Speed of the object"),
                       _("Test the overall speed of an object"),
                       _("The speed of _PARAM0_ is _PARAM2_ _PARAM1_"),
                       _("Displacement"),
                       "res/conditions/vitesse24.png",
                       "res/conditions/vitesse.png")

            .AddParameter("object", _("Object"))
            .AddParameter("expression", _("Speed"))
            .AddParameter("relationalOperator", _("Sign of the test"))
            .codeExtraInformation.SetFunctionName("TotalForceLength").SetManipulatedType("number");

        obj.AddCondition("AngleOfDisplacement",
                       _("Angle of moving"),
                       _("Test the angle of displacement of an object"),
                       _("The angle of displacement of _PARAM0_ is _PARAM1_ ( tolerance : _PARAM2_� )"),
                       _("Displacement"),
                       "res/conditions/vitesse24.png",
                       "res/conditions/vitesse.png")

            .AddParameter("object", _("Object"))
            .AddParameter("expression", _("Angle, in degrees"))
            .AddParameter("expression", _("Tolerance"))
            .codeExtraInformation.SetFunctionName("TestAngleOfDisplacement");

        obj.AddCondition("AutomatismActivated",
                       _("Automatism activated"),
                       _("Return true if the automatism is activated for the object."),
                       _("Automatism _PARAM1_ of _PARAM0_ is activated"),
                       _("Automatisms"),
                       "res/automatism24.png",
                       "res/automatism16.png")

            .AddParameter("object", _("Object"))
            .AddParameter("automatism", _("Automatism"))
            .codeExtraInformation.SetFunctionName("AutomatismActivated");

        obj.AddAction("ActivateAutomatism",
                       _("De/activate an automatism"),
                       _("De/activate the automatism for the object."),
                       _("Activate automatism _PARAM1_ of _PARAM0_: _PARAM2_"),
                       _("Automatisms"),
                       "res/automatism24.png",
                       "res/automatism16.png")

            .AddParameter("object", _("Object"))
            .AddParameter("automatism", _("Automatism"))
            .AddParameter("yesorno", _("Activate \?"))
            .codeExtraInformation.SetFunctionName("ActivateAutomatism");


        obj.AddAction("AddForceVers",
                       _("Add a force so as to move to an object"),
                       _("Add a force to an object so as it moves to another."),
                       _("Move _PARAM0_ to _PARAM1_ with a force of _PARAM2_ pixels"),
                       _("Displacement"),
                       "res/actions/forceVers24.png",
                       "res/actions/forceVers.png")

            .AddParameter("object", _("Object"))
            .AddParameter("object", _("Target Object"))
            .AddParameter("expression", _("Length in pixel"))
            .AddParameter("expression", _("Damping ( Default : 0 )"))
            .AddCodeOnlyParameter("ptrToObjectOfParameter", "1")
            .codeExtraInformation.SetFunctionName("AddForceTowardObject").SetIncludeFile("GDL/BuiltinExtensions/ObjectTools.h");


        obj.AddAction("AddForceTourne",
                       _("Add a force so as to move around an object"),
                       _("Add a force to an object so as it rotates around another.\nNote that the moving is not precise, especially if the speed is high.\nTo position an object around a position more precisly, use the actions in the category  \"Position\"."),
                       _("Rotate _PARAM0_ around _PARAM1_ with _PARAM2_�/sec and _PARAM3_ pixels away"),
                       _("Displacement"),
                       "res/actions/forceTourne24.png",
                       "res/actions/forceTourne.png")

            .AddParameter("object", _("Object"))
            .AddParameter("object", _("Rotate around this object"))
            .AddParameter("expression", _("Speed ( Degrees per second )"))
            .AddParameter("expression", _("Distance ( in pixel )"))
            .AddParameter("expression", _("Damping ( Default : 0 )"))
            .AddCodeOnlyParameter("ptrToObjectOfParameter", "1")
            .codeExtraInformation.SetFunctionName("AddForceToMoveAroundObject").SetIncludeFile("GDL/BuiltinExtensions/ObjectTools.h");


        obj.AddAction("MettreAutour",
                       _("Put an object around another"),
                       _("Position an object around another, with the specified angle and distance."),
                       _("Put _PARAM0_ around _PARAM1_, with an angle of _PARAM3_� and _PARAM2_ pixels distance."),
                       _("Position"),
                       "res/actions/positionAutour24.png",
                       "res/actions/positionAutour.png")

            .AddParameter("object", _("Object"))
            .AddParameter("object", _("\"Center\" Object"))
            .AddParameter("expression", _("Distance"))
            .AddParameter("expression", _("Angle, in degrees"))
            .AddCodeOnlyParameter("ptrToObjectOfParameter", "1")
            .codeExtraInformation.SetFunctionName("PutAroundObject").SetIncludeFile("GDL/BuiltinExtensions/ObjectTools.h");


        //Deprecated action
        obj.AddAction("Rebondir",
                       _("Move an object away from another"),
                       _("Move an object away from another, using forces."),
                       _("Move away _PARAM0_ of _PARAM1_ ( only _PARAM0_ will move )"),
                       _("Displacement"),
                       "res/actions/ecarter24.png",
                       "res/actions/ecarter.png")

            .SetHidden()
            .AddParameter("object", _("Object"))
            .AddParameter("object", _("Object 2 ( won't move )"))
            .AddCodeOnlyParameter("mapOfObjectListsOfParameter", "1")
            .codeExtraInformation.SetFunctionName("SeparateObjectsWithForces").SetIncludeFile("GDL/BuiltinExtensions/ObjectTools.h");


        //Deprecated action
        obj.AddAction("Ecarter",
                       _("Move an object away from another"),
                       _("Move an object away from another without using forces."),
                       _("Move away _PARAM0_ of _PARAM2_ ( only _PARAM0_ will move )"),
                       _("Position"),
                       "res/actions/ecarter24.png",
                       "res/actions/ecarter.png")

            .SetHidden()
            .AddParameter("object", _("Object"))
            .AddParameter("object", _("Object 2 ( won't move )"))
            .AddCodeOnlyParameter("mapOfObjectListsOfParameter", "1")
            .codeExtraInformation.SetFunctionName("SeparateObjectsWithoutForces").SetIncludeFile("GDL/BuiltinExtensions/ObjectTools.h");


        obj.AddAction("SeparateFromObjects",
                       _("Separate two objects"),
                       _("Move an object away from another using their collision masks.\nBe sure to call this action on a reasonable number of objects so as\nnot to slow down the game."),
                       _("Move away _PARAM0_ of _PARAM1_ ( only _PARAM0_ will move )"),
                       _("Position"),
                       "res/actions/ecarter24.png",
                       "res/actions/ecarter.png")

            .AddParameter("object", _("Object"))
            .AddParameter("object", _("Objects"))
            .AddCodeOnlyParameter("mapOfObjectListsOfParameter", "1")
            .codeExtraInformation.SetFunctionName("SeparateFromObjects").SetIncludeFile("GDL/BuiltinExtensions/ObjectTools.h");

        obj.AddExpression("ForceX", _("Average X coordinates of forces"), _("Average X coordinates of forces"), _("Displacement"), "res/actions/force.png")
            .AddParameter("object", _("Object"))
            .codeExtraInformation.SetFunctionName("TotalForceX");

        obj.AddExpression("ForceY", _("Average Y coordinates of forces"), _("Average Y coordinates of forces"), _("Displacement"), "res/actions/force.png")
            .AddParameter("object", _("Object"))
            .codeExtraInformation.SetFunctionName("TotalForceY");

        obj.AddExpression("ForceAngle", _("Average angle of the forces"), _("Average angle of the forces"), _("Displacement"), "res/actions/force.png")
            .AddParameter("object", _("Object"))
            .codeExtraInformation.SetFunctionName("TotalForceAngle");

        obj.AddExpression("Angle", _("Average angle of the forces"), _("Average angle of the forces"), _("Displacement"), "res/actions/force.png")
            .AddParameter("object", _("Object"))

            .SetHidden()
            .codeExtraInformation.SetFunctionName("TotalForceAngle");

        obj.AddExpression("ForceLength", _("Average length of the forces"), _("Average length of the forces"), _("Displacement"), "res/actions/force.png")
            .AddParameter("object", _("Object"))
            .codeExtraInformation.SetFunctionName("TotalForceLength");

        obj.AddExpression("Longueur", _("Average length of the forces"), _("Average length of the forces"), _("Displacement"), "res/actions/force.png")
            .AddParameter("object", _("Object"))

            .SetHidden()
            .codeExtraInformation.SetFunctionName("TotalForceLength");

        obj.AddExpression("Distance", _("Distance between two objects"), _("Distance between two objects"), _("Position"), "res/conditions/distance.png")
            .AddParameter("object", _("Object"))
            .AddParameter("object", _("Object"))
            .AddCodeOnlyParameter("ptrToObjectOfParameter", "1")
            .codeExtraInformation.SetFunctionName("GetDistanceWithObject");

        obj.AddExpression("SqDistance", _("Square distance between two objects"), _("Square distance between two objects"), _("Position"), "res/conditions/distance.png")
            .AddParameter("object", _("Object"))
            .AddParameter("object", _("Object"))
            .AddCodeOnlyParameter("ptrToObjectOfParameter", "1")
            .codeExtraInformation.SetFunctionName("GetSqDistanceWithObject");
*/
/*

    AddAction("CreateByName",
                   _("Create an object from its name"),
                   _("Among the objects of the specified group, the action will create the object with the specified name."),
                   _("Among objects _PARAM2_, create object named _PARAM3_ at position _PARAM4_;_PARAM5_"),
                   _("Objects"),
                   "res/actions/create24.png",
                   "res/actions/create.png")
        .AddCodeOnlyParameter("currentScene", "")
        .AddCodeOnlyParameter("mapOfObjectListsOfParameterWithoutPicking", "2")
        .AddParameter("object", _("Groups containing objects which can be created by the action"))
        .AddParameter("string", _("Text representing the name of the object to create"))
        .AddParameter("expression", _("X position"))
        .AddParameter("expression", _("Y position"))
        .AddParameter("layer", _("Layer ( Base layer if empty )"), "", true).SetDefaultValue("\"\"")
        .codeExtraInformation.SetFunctionName("CreateObjectFromGroupOnScene").SetIncludeFile("GDL/BuiltinExtensions/RuntimeSceneTools.h");

    AddAction("AjoutObjConcern",
                   _("Consider objects"),
                   _("Pick all objects with this name."),
                   _("Consider all _PARAM3_ "),
                   _("Objects"),
                   "res/actions/add24.png",
                   "res/actions/add.png")
        .AddCodeOnlyParameter("currentScene", "")
        .AddCodeOnlyParameter("mapOfObjectListsOfParameter", "3")
        .AddCodeOnlyParameter("inlineCode", "0")
        .AddParameter("object", _("Object"))
        .codeExtraInformation.SetFunctionName("PickAllObjects").SetIncludeFile("GDL/BuiltinExtensions/RuntimeSceneTools.h");

    AddAction("AjoutHasard",
                   _("Take a random object"),
                   _("Take only one object with this name among all"),
                   _("Take a random _PARAM3_ "),
                   _("Objects"),
                   "res/actions/ajouthasard24.png",
                   "res/actions/ajouthasard.png")
        .AddCodeOnlyParameter("currentScene", "")
        .AddCodeOnlyParameter("mapOfObjectListsOfParameter", "3")
        .AddCodeOnlyParameter("inlineCode", "0")
        .AddParameter("object", _("Object"))
        .codeExtraInformation.SetFunctionName("PickRandomObject").SetIncludeFile("GDL/BuiltinExtensions/RuntimeSceneTools.h");

    AddAction("MoveObjects",
                   _("Make objects moving"),
                   _("Moves the objects according to the forces they have.Game Develop call this action at the end of the events by default."),
                   _("Make objects moving"),
                   _("Displacement"),
                   "res/actions/doMove24.png",
                   "res/actions/doMove.png")
        .AddCodeOnlyParameter("currentScene", "")
        .codeExtraInformation.SetFunctionName("MoveObjects").SetIncludeFile("GDL/BuiltinExtensions/RuntimeSceneTools.h");

    AddCondition("SeDirige",
                   _("An object is moving to another"),
                   _("Test if an object moves towards another.\nThe first object must move."),
                   _("_PARAM0_ is moving to _PARAM1_"),
                   _("Displacement"),
                   "res/conditions/sedirige24.png",
                   "res/conditions/sedirige.png")
        .AddParameter("object", _("Object"))
        .AddParameter("object", _("Object 2"))
        .AddCodeOnlyParameter("mapOfObjectListsOfParameter", "0")
        .AddCodeOnlyParameter("mapOfObjectListsOfParameter", "1")
        .AddParameter("expression", _("Angle of tolerance"))
        .AddCodeOnlyParameter("conditionInverted", "")
        .codeExtraInformation.SetFunctionName("MovesToward").SetIncludeFile("GDL/BuiltinExtensions/ObjectTools.h");



    AddCondition("Distance",
                   _("Distance between two objects"),
                   _("Test the distance between two objects."),
                   _("The distance between _PARAM0_ and _PARAM1_ is _PARAM5__PARAM4_"),
                   _("Position"),
                   "res/conditions/distance24.png",
                   "res/conditions/distance.png")
        .AddParameter("object", _("Object"))
        .AddParameter("object", _("Object 2"))
        .AddCodeOnlyParameter("mapOfObjectListsOfParameter", "0")
        .AddCodeOnlyParameter("mapOfObjectListsOfParameter", "1")
        .AddParameter("expression", _("Distance"))
        .AddParameter("relationalOperator", _("Sign of the test"))
        .AddCodeOnlyParameter("conditionInverted", "")
        .codeExtraInformation.SetFunctionName("DistanceBetweenObjects").SetIncludeFile("GDL/BuiltinExtensions/ObjectTools.h");



    AddCondition("AjoutObjConcern",
                   _("Consider objects"),
                   _("Pick all objects with this name."),
                   _("Consider all _PARAM3_ "),
                   _("Objects"),
                   "res/conditions/add24.png",
                   "res/conditions/add.png")
        .AddCodeOnlyParameter("currentScene", "")
        .AddCodeOnlyParameter("mapOfObjectListsOfParameter", "3")
        .AddCodeOnlyParameter("inlineCode", "0")
        .AddParameter("object", _("Object"))
        .codeExtraInformation.SetFunctionName("PickAllObjects").SetIncludeFile("GDL/BuiltinExtensions/RuntimeSceneTools.h");



    AddCondition("AjoutHasard",
                   _("Take a random object"),
                   _("Take only one object with this name among all"),
                   _("Take a random _PARAM3_ "),
                   _("Objects"),
                   "res/conditions/ajouthasard24.png",
                   "res/conditions/ajouthasard.png")
        .AddCodeOnlyParameter("currentScene", "")
        .AddCodeOnlyParameter("mapOfObjectListsOfParameter", "3")
        .AddCodeOnlyParameter("inlineCode", "0")
        .AddParameter("object", _("Object"))
        .codeExtraInformation.SetFunctionName("PickRandomObject").SetIncludeFile("GDL/BuiltinExtensions/RuntimeSceneTools.h");



    AddCondition("CollisionNP", //"CollisionNP" cames from an old condition to test collision between two sprites non precisely.
                   _("Collision"),
                   _("Test the collision between two objects using their collision mask.\nNote that some objects may not have a collision mask.\nSome others, like Sprite, provide also more precise collision conditions."),
                   _("_PARAM0_ is in collision with _PARAM1_ ( Collision masks )"),
                   _("Collision"),
                   "res/conditions/collision24.png",
                   "res/conditions/collision.png")
        .AddParameter("object", _("Object"))
        .AddParameter("object", _("Object"))
        .AddCodeOnlyParameter("mapOfObjectListsOfParameter", "0")
        .AddCodeOnlyParameter("mapOfObjectListsOfParameter", "1")
        .AddCodeOnlyParameter("conditionInverted", "")
        .codeExtraInformation.SetFunctionName("HitBoxesCollision").SetIncludeFile("GDL/BuiltinExtensions/ObjectTools.h");
*/
}