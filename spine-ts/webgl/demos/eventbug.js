var eventBugDemo = function(canvas, bgColor) {
    var assetManager;

    var DEMO_NAME = "Event Bug Demo";

    function init () {
        assetManager = spineDemos.assetManager;
        assetManager.loadJson(DEMO_NAME, "EventBug.json");
    }

    function loadingComplete () {
        startTest(loadSkeleton("Skeleton"));
    }

    function startTest (skeletonObjects) {
        var skeleton = skeletonObjects.skeleton,
            animationState = skeletonObjects.state,
            trackEntry,
            t = 0;

        trackEntry = animationState.setAnimation(0, 'event', false);
        trackEntry.listener = {
            event: function(entry, event) {
                console.log(event.data.name, event.stringValue, t);
            }
        }
        trackEntry.eventThreshold = 1.1;

        trackEntry = animationState.addAnimation(0, 'event', 0, false);
        trackEntry.mixDuration = 0.05; // The track entry must be fully mixed in at the frame of the event (which is at 0.1 seconds)
        trackEntry.delay -= 0.250;

        // Bug is apparent when waiting between 52 and 101 ticks
        // while the current animation is mixing in and the
        // mixingFrom entry has not yet triggered its event.
        for (; t < 70; t++) {
            update(skeleton, animationState, 0.001);
        }

        trackEntry = animationState.setAnimation(0, 'event', false);
        trackEntry.mixDuration = 1.250; // The event is triggered every frame from 0.1 s until this track entry is done mixing.

        for (; t < 1800; t++) {
            update(skeleton, animationState, 0.001);
        }
    }

    function update (skeleton, animationState, dt) {
        animationState.update(dt);
        animationState.apply(skeleton);
        skeleton.updateWorldTransform();
    }

    function loadSkeleton(name, animation, sequenceSlots) {
        var attachmentLoader = {
            'newRegionAttachment': function() {},
            'newBoundingBoxAttachment': function() {},
            'newMeshAttachment': function() {},
            'newPathAttachment': function() {},
            'newPointAttachment': function() {},
            'newClippingAttachment': function() {}
        };

        var skeletonJson = new spine.SkeletonJson(attachmentLoader);
        var skeletonData = assetManager.get(DEMO_NAME, "EventBug.json");
        var spineSkeletonData = skeletonJson.readSkeletonData(skeletonData);
        var skeleton = new spine.Skeleton(spineSkeletonData);
        var state = new spine.AnimationState(new spine.AnimationStateData(spineSkeletonData));

        return {
            skeleton: skeleton,
            state: state,
        };
    }

    function render () {
    }

    eventBugDemo.loadingComplete = loadingComplete;
    eventBugDemo.render = render;
    eventBugDemo.DEMO_NAME = DEMO_NAME;
    init();
};
